
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <stdio.h>

#include "lxt_write.h"

int main(int argc, char **argv)
{

    struct lt_trace *trace = lt_init("trace.lxt");
    lt_set_timescale(trace, -9); /* nsec */

    int first = 1;

    char buf[256];
    while(fgets(buf, sizeof(buf), stdin)) {

        char *p = strchr(buf, '\n');
        if(p) *p = '\0';

        char *what = strtok(buf, " ");
        if(what == NULL) continue;

        char *tstr = strtok(NULL, " ");
        if(tstr == NULL) continue;
        uint64_t t = strtoll(tstr, NULL, 10);
        
        char *msg = strtok(NULL, " ");
        if(msg == NULL) continue;
        
        char *data = strtok(NULL, " ");
        if(data == NULL) data = ".";

        struct lt_symbol *sym = lt_symbol_find(trace, msg);
        if(sym == NULL) {
            sym = lt_symbol_add(trace, msg, 0, 0, 0, LT_SYM_F_STRING);
        }
   
        if(first) {
            lt_set_timezero(trace, -t);
            first = 0;
        }

        lt_set_time64(trace, t);

        printf("%s %" PRIu64 " %s '%s'\n", what, t, msg, data);

        if(what[0] == '+') {
            lt_emit_value_string(trace, sym, 0, data);
        } else {
            lt_emit_value_string(trace, sym, 0, "");
        }

    }


    lt_close(trace);

    return(0);

}
