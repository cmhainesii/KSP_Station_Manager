#include "include/devices.hpp"


  KSP_SM::DockingPortCount::DockingPortCount(std::array<std::size_t, 5> counts)
    {
        this->xs = counts.at(0);
        this->sm = counts.at(1);
        this->md = counts.at(2);
        this->lg = counts.at(3);
        this->xl = counts.at(4);
    }
        // std::size_t C16;
        // std::size_t C16S;
        // std::size_t C8888;
        // std::size_t CSDTS;
        // std::size_t CHG5;
        // std::size_t CHG55;
        // std::size_t RA15;
        // std::size_t RA2;
        // std::size_t RA100;
    KSP_SM::CommsDevCount::CommsDevCount(std::array<std::size_t, 9> counts)
    {
        C16 = counts.at(0);
        C16S = counts.at(1);
        C8888 = counts.at(2);
        CDTS = counts.at(3);
        CHG5 = counts.at(4);
        CHG55 = counts.at(5);
        RA15 = counts.at(6);
        RA2 = counts.at(7);
        RA100 = counts.at(8);
        
    }