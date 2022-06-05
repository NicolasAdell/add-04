#include <stdio.h>
#include "pico/stdlib.h"

#define ECHO 27
#define TRIGGER 28

int main() {

    stdio_init_all();
    gpio_init(TRIGGER);
    gpio_set_dir(TRIGGER, true);
    gpio_init(ECHO);
    gpio_set_dir(ECHO, false);
    
    while (1){
        
        gpio_put(TRIGGER, true);
        absolute_time_t t0 = get_absolute_time();
        sleep_us(10);
        gpio_put(TRIGGER, false);

        absolute_time_t t1;
        uint64_t t;
        
        while(gpio_get(ECHO) == false){
            t1 = get_absolute_time();
            t = absolute_time_diff_us(t0, t1);
            
            if ( t >= 25000 ){
                break;
            }
        }
        float d = (t*343) / (2*1000000);
        printf("La distancia es %.3f m\n", d);
    }
}