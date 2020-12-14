#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <random>
#include <cmath>

using namespace std;

double calculate_one_envelope(unsigned int remaining_number, double remaining_money)
{
    random_device rd{};
    mt19937 engine{rd()};
    uniform_real_distribution<double> dist{0.0, 1.0};
    double random_number_between_0_and_1 = dist(engine);
    double envelope_money = 0.01 + ceil(100 * (random_number_between_0_and_1 * (2 * (remaining_money / remaining_number) - 0.01))) / 100;
    return envelope_money;
}

vector<pair<unsigned int, double>> simulate_once(unsigned int red_envelope_number, double red_envelope_money)
{
    vector<pair<unsigned int, double>> red_envelope_list;
    unsigned int remaining_number = red_envelope_number;
    double remaining_money = red_envelope_money;

    for(int i = 0; i < red_envelope_number; i++)
    {
        if(i == red_envelope_number - 1)
        {
            unsigned int single_envelope_number = red_envelope_number;
            double single_envelope_money = remaining_money;
            red_envelope_list.push_back(make_pair(single_envelope_number, single_envelope_money));
        }
        else
        {
            unsigned int single_envelope_number = i + 1;
            double single_envelope_money = calculate_one_envelope(remaining_number, remaining_money);
            red_envelope_list.push_back(make_pair(single_envelope_number, single_envelope_money));
            remaining_number = remaining_number - 1;
            remaining_money = remaining_money - single_envelope_money;
        }
    }

    return red_envelope_list;
}

void print_forms(vector<pair<unsigned int, double>> red_envelope_list)
{
    fstream iofile;
    iofile.open("output.csv", ios::app);
    iofile << "Sequence" << "," << "Money" << endl;
    for(auto single_red_envelope : red_envelope_list)
    {
        cout << "取样顺序：" << single_red_envelope.first << " " << "红包金额：" << single_red_envelope.second << endl;
        iofile << single_red_envelope.first << "," <<single_red_envelope.second << endl;
    }
    iofile.close();
}

int main()
{
    ios::sync_with_stdio(false);
    unsigned int red_envelope_number = 0;
    double red_envelope_money = 0;
    int repeat_times = 0;

    cout << "请输入分配的红包数量：" << endl;
    cin >> red_envelope_number;
    cout << "请输入红包总金额：" << endl;
    cin >> red_envelope_money;
    cout << "请输入重复次数：" << endl;
    cin >> repeat_times; 

    for(int i = 0; i < repeat_times; i++)
    {
        cout << "第" << i + 1 << "次测试" << endl;
        vector<pair<unsigned int, double>> red_envelope_list = simulate_once(red_envelope_number, red_envelope_money);
        print_forms(red_envelope_list);
    }
    return 0;
}