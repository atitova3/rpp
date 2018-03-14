#include <iostream>
#include <vector>
using namespace std;

void go_out (vector<int>& mass)
{
	for (int i = 0; i < mass.size(); i++)
	{
		if (mass[i] == 0)
		{
			cout << "... ";
		}
		else
		{
			if (mass[i] < 0)
			{
				cout << "[" << -1*mass[i] << "] ";
			}
			else
			{
				cout << mass[i] << " ";
			}
		}
	}
	return;
}

void present (int i, int now, vector <int>& mass)
{
	if (i == now)
	{
		mass.push_back(-1*i);
		//cout << mass[mass.size() - 1];//
		//cout << "[" << i << "] ";
	}
	else
	{
		mass.push_back(i);
		//cout << mass[mass.size() - 1];//
		//cout << i << " ";
	}
	return;
}

void writing (int kod, vector <int>& mass)
{
	if (kod == -1)
	{
		mass.push_back(0);
		go_out(mass);
		//cout << "... ";
	}
	else
	{
		if (kod == 1)
		{
			mass.push_back(1);
			mass.push_back(0);
			//cout << "1 ... ";
		}
		else
		{
			mass.push_back(0);
			mass.push_back(kod);
			//cout << "... " << kod;
		}
	}
	return;
}

vector<int> vuvod(int all, int now, int wid)
{
	vector <int> mass;
	if (all <= 3)
	{
		for (int i = 1; i <= all; i++)
		{
			present(i, now, mass);//write original numbers
			//cout << "Pusto " << mass.empty();//
		}
	}
	else
	{
		if (now <= wid)
		{
			for (int i = 1; i <= wid; i ++)
			{
				present(i, now, mass);
				//cout << "Pusto " << mass.empty();//
			}
			writing(all, mass);//writing no original symb-s
			//cout << "Pusto " << mass.empty();//
		}
		else
		{
			if ((all - now) <= wid)
			{
				writing(1, mass);
				//cout << "Pusto " << mass.empty();//
				for (int i = all - wid + 1; i <= all; i++)
				{
					present(i, now, mass);
					//cout << "Pusto " << mass.empty();//
				}
			}
			else
			{
				writing(1, mass);
				//cout << "Pusto " << mass.empty();//
				int midd = wid/2;
				for (int i = now - midd; i < now + wid - midd; i++)
				{
					present(i, now, mass);
					//cout << "Pusto " << mass.empty();//
				}
				writing(all, mass);
				//cout << "Pusto " << mass.empty();//
			}
		}
	}
	//cout << endl;
	return mass;
}

int main()
{
	int rep = 1;
	do
	{
		int all_page;
		int now_page;
		int wid_page;
		cout << "Inside kol-vo pages of this text: ";
		cin >> all_page;
		cout << "Inside number of presently page: ";
		cin >> now_page;
		cout << "Inside width of page navigation: ";
		cin >> wid_page;
		//vuvod(all_page, now_page, wid_page);
		vector<int> new_mass = vuvod(all_page, now_page, wid_page);
		go_out(new_mass);
		cout << endl;
		cout << "If you want repaet, inside 1, else inside 0: ";
		cin >> rep;
		cout << endl;
	}
	while (rep == 1);
}
