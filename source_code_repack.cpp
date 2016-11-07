#include<iostream>
#include<fstream>
#include<vector>

int main()
{
    std::ifstream fin("c.in");

    short int bus_num, bus_size, people_num;
    fin >> bus_num;
    fin >> bus_size;
    fin >> people_num;
    std::vector<int> people_sizes (people_num);
    for (int i = 0;i < people_num; ++i)
    {
        fin >> people_sizes[i];
    }


    std::vector<std::vector<std::vector<int>>>
    result(bus_num, std::vector<std::vector<int>>
    (people_num+1, std::vector<int>(bus_size+1)));

    for (int i = 0; i < bus_num; ++i)
    {
        for (int j = 0; j < people_num + 1; ++j)
        {
            for (int k = 0;k < bus_size + 1; ++k)
            {
                result[i][j][k] = 0;
            }
        }
    }
    result[0][0][0] = 0;
    for (int bus_iter = 0; bus_iter < bus_num; ++bus_iter)
    {
        for (int people_iter = 1; people_iter <= people_num; ++people_iter)
        {
            if (bus_iter > 0)
            {
                result[bus_iter][people_iter][0] = result[bus_iter - 1][people_iter][bus_size];
            }
            else
            {
                result[bus_iter][people_iter][0] = 0;
            }
            for (int chek_iter = 1; chek_iter <= bus_size; ++chek_iter)
            {
                if (chek_iter < people_sizes[people_iter - 1])
                {
                    result[bus_iter][people_iter][chek_iter] = std::max(
                     (result[bus_iter][people_iter - 1][chek_iter]), 
                    (result[bus_iter][people_iter][chek_iter - 1]));
                }
                else
                {
                    result[bus_iter][people_iter][chek_iter] = std::max(
                        (result[bus_iter][people_iter - 1][chek_iter]),
                        (1 + result[bus_iter][people_iter - 1]
                         [chek_iter - people_sizes[people_iter - 1]])
                        );
                }
            }
        }
    }
    
    std::ofstream fout("c.out");

    fout << result[bus_num - 1][people_num][bus_size];
    fout.close();
    fin.close();
    return 0;
}
