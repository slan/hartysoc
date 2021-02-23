#include <iostream>
#include "top.cpp"

int main()
{
    cxxrtl_design::p_top top;
    uint32_t pc;

    top.step();
    top.p_pll_2e_rs__hart_2e_stage1.set<bool>(false);
    for(int cycle=0;cycle<5;++cycle){

        top.p_hart__clk.set<bool>(false);
        top.step();
        pc    = top.p_hart_2e_pc.get<uint32_t>();
        std::cout << pc << std::endl;
        top.p_hart__clk.set<bool>(true);
        top.step();
        pc    = top.p_hart_2e_pc.get<uint32_t>();
        std::cout << pc << std::endl;
        

        // bool cur_led        = top.p_led.get<bool>();
        // uint32_t counter    = top.p_counter.get<uint32_t>();

        // if (cur_led != prev_led){
        //     cout << "cycle " << cycle << " - led: " << cur_led << ", counter: " << counter << endl;
        // }
        // prev_led = cur_led;
    }
}
