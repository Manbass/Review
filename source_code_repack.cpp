#include<iostream>
#include<fstream>
#include<vector>

void read (int & bus_num, int & bus_size, int & people_num,
           std::vector<int> & people_sizes, std::istream & in)
{
	in >> bus_num >> bus_size >> people_num;
	people_sizes.resize (people_num);
	for (int i = 0 ; i < people_num; ++i)
	{
		in >> people_sizes[i];
	}
	return;
}

void write (std::ostream & out, int max_people)
{
	out << max_people;
	return;
}

int processing (int bus_num, int bus_size, int people_num, std::vector<int> & people_sizes)
{
	//3D arrow
	 std::vector<
		 std::vector<
			std::vector<int>>> max_peoples;

	 max_peoples.resize (bus_num,
							std::vector<
								std::vector<int>> (people_num+1,
									std::vector<int> (bus_size+1)));	

	for (int i = 0; i < bus_num; ++i)
    {
        for (int j = 0; j < people_num + 1; ++j)
        {
            for (int k = 0;k < bus_size + 1; ++k)
            {
                max_peoples[i][j][k] = 0;
            }
        }
    }

    for (int bus_iter = 0; bus_iter < bus_num; ++bus_iter)
    {
        for (int people_iter = 1; people_iter <= people_num; ++people_iter)
        {
            if (bus_iter > 0)
            {
                max_peoples[bus_iter][people_iter][0] = max_peoples[bus_iter - 1][people_iter][bus_size];
            }
            else
            {
                max_peoples[bus_iter][people_iter][0] = 0;
            }
            for (int chek_iter = 1; chek_iter <= bus_size; ++chek_iter)
            {
                if (chek_iter < people_sizes[people_iter - 1])
                {
                    max_peoples[bus_iter][people_iter][chek_iter] = std::max(
                     (max_peoples[bus_iter][people_iter - 1][chek_iter]), 
                    (max_peoples[bus_iter][people_iter][chek_iter - 1]));
                }
                else
                {
                    max_peoples[bus_iter][people_iter][chek_iter] = std::max(
                        (max_peoples[bus_iter][people_iter - 1][chek_iter]),
                        (1 + max_peoples[bus_iter][people_iter - 1]
                         [chek_iter - people_sizes[people_iter - 1]])
                        );
                }
            }
        }
    }
	return max_peoples[bus_num - 1][people_num][bus_size];
}

int main()
{
	int bus_num, bus_size, people_num;
    std::vector<int> people_sizes;

    std::ifstream fin("c.in"); 
	read (bus_num, bus_size, people_num, people_sizes, fin); 
    
    std::ofstream fout("c.out");
	write (fout, processing (bus_num, bus_size, people_num, people_sizes));

    fout.close();
    fin.close();
    return 0;
}
