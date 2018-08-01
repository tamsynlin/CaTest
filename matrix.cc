#include <string>
#include <vector>
#include <map>
#include <utility>
#include <iostream>

using namespace std;

using array_list = vector<string>;

class matrix
{
public:
    matrix(array_list &name_set, vector<array_list> &data_set)
        : m_names(move(name_set)), m_data(move(data_set))
    {
        ;
    }
    ~matrix() {};

    void print_matrix() const
    {
        for (auto &name: m_names)
        {
            cout << name << endl;
        }

        for (auto &data: m_data)
        {
            for (auto &item : data)
            {
                cout << item << " ";
            }

            cout << endl;
        }
    }

    matrix& add(matrix &aOther) const
    {
        array_list names;
        vector<array_list> data;

        if (this->m_names == aOther.m_names)
        {
            names = this->m_names;
            data = this->m_data;

            data.insert(data.end(), aOther.m_data.begin(), aOther.m_data.end());
        }
        else
        {
            //merge the data
            map <string, int> key_map;
            
            for (const auto &name: this->m_names)
            {
                key_map[name] = 0;
                names.push_back(name);
            }

            for (const auto &name: aOther.m_names)
            {
                if (key_map.find(name) == key_map.end())
                {
                    key_map[name] = 0;
                    names.push_back(name);
                }
                else
                {
                    key_map[name]++;
                }
            }

            int length = key_map.size();
            int gap_this = length - this->m_names.size();
            int gap_other = length - aOther.m_names.size();

            vector<array_list> new_data;

            for (auto data : this->m_data)
            {
                for (int i=0; i<gap_this; i++)
                {
                    data.push_back("*");
                }

                new_data.push_back(data);
            }

            data = new_data;

            vector<array_list> new_data_other;

            for (auto data : aOther.m_data)
            {
                for (int i=0; i<gap_other; i++)
                {
                    data.insert(data.begin(), "*");
                }

                new_data_other.push_back(data);
            }

            data.insert(data.end(), new_data_other.begin(), new_data_other.end());
        }

        return *(new matrix(names, data));
    }

private:
    array_list         m_names;
    vector<array_list> m_data;
};

int main(int argc, char const *argv[])
{
    /* code */
    array_list names = {"a", "b"};
    vector<array_list> data = {{"1", "2"}, {"3", "4"}};

    matrix mx = matrix(names, data);
    mx.print_matrix();

    matrix copy = mx;

    matrix &sum = copy.add(mx);
    sum.print_matrix();

    array_list other_names = {"c", "d"};
    vector<array_list> other_data = {{"3", "4"}, {"5", "6"}};
    matrix other = matrix(other_names, other_data);

    matrix &new_sum = sum.add(other);
    new_sum.print_matrix();

    delete &sum;
    delete &new_sum;

    return 0;
}
