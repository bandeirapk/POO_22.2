#include <iostream>
#include <sstream>
#include <aux.hpp>


struct Car {

    int pass {0};
    int passMax {2};
    int gas {0};
    int gasMax {100};
    int km {0};

    Car() {
    }

    void enter() { 
        if (pass == passMax)
            std::cout << "fail: limite de pessoas atingido\n";
        else
            pass++;
    }

    void leave() { 
        if (pass == 0) 
            std::cout << "fail: nao ha ninguem no carro\n";
        else
            pass--;
    }

    void fuel(int gas) { 
        if (gas <= gasMax)   
            this->gas += gas;
        else
            this->gas = gas - gasMax;
    }

    void drive(int km){   
        if (pass == 0) {
            std::cout << "fail: nao ha ninguem no carro\n";
        } else if (pass >= 1 && gas >= km)  {
            gas -= km;
            this->km += km;
        } else if (gas == 0 && km > gas) {
            std::cout << "fail: tanque vazio\n";
        } else if (pass >= 1 && km > gas) {
            if (km > gasMax) {
                gas -= 100;
                this->km += 100;
            }

            std::cout << "fail: tanque vazio apos andar " << gas << " km\n"; 
            this->km += gas;
            gas = 0;
        }
}

    std::string str() {
        std::stringstream ss;
        ss << "pass: " << pass << ", gas: " << gas << ", km: " << km << "";
        return ss.str();
    }
};

int main() {
    aux::Chain chain;
    aux::Param ui;

    Car car;

    chain["help"]  = [&](){ aux::show << "show; enter; leave; fuel _gas; drive _km; end"; };
    chain["show"]  = [&](){ aux::show << car.str(); };
    chain["enter"] = [&](){ car.enter(); };
    chain["leave"] = [&](){ car.leave(); };
    chain["fuel"]  = [&](){ car.fuel(aux::to<int>(ui[1])); };
    chain["drive"] = [&](){ car.drive(aux::to<int>(ui[1])); };

    aux::execute(chain, ui);
}
