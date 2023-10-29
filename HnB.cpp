#include <iostream>
#include <vector>
#include <random>
#include <algorithm>	
using namespace std;

struct Candidate { //数字の組の中身
	int n0 = 0, n1 = 0, n2 = 0;
};

struct Counts { //count:何回あった，nsum:何手かかったかの総和
	int count = 0;
	float nsum = 0;
};

void MakeCan(int i, int j, int k, vector<Candidate>& Cans) {
	Candidate Can;
	Can.n0 = i;
	Can.n1 = j;
	Can.n2 = k;
	Cans.push_back(Can);
}

vector<int> Hint(vector<int> comp1, vector<int> comp2, vector<int> hint) { //CompはCompare，比較対象のこと
	//vector<int> hint{ 0, 0 };

	if (comp1[0] == comp2[0]) hint[0]++;
	if (comp1[1] == comp2[1]) hint[0]++;
	if (comp1[2] == comp2[2]) hint[0]++;
	for (int i = 0; i < 2; ++i) {
		int avoid = comp1[0];
		comp1.erase(comp1.begin());
		comp1.push_back(avoid);
		if (comp1[0] == comp2[0]) ++hint[1];
		if (comp1[1] == comp2[1]) ++hint[1];
		if (comp1[2] == comp2[2]) ++hint[1];
	}
	int avoid = comp1[0];
	comp1.erase(comp1.begin());
	comp1.push_back(avoid);

	return hint;
	//std::cout << "(" << comp1[0] << "," << comp1[1] << "," << comp1[2] << "), " << "(" << hint[0] << "," << hint[1] << ")" << endl;
}

int main() {

	vector<Candidate> Canori, Cans; //候補プール
	vector<Counts> C1Hint;
	Counts C00, C01, C02, C03, C10, C11, C12, C20, C30;

	float sum = 0;
	const int times = 10000;

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			if (i == j) {
				continue;
			}
			for (int k = 0; k < 10; ++k) {
				if (i == k || j == k) {
					continue;
				}
				MakeCan(i, j, k, Canori);
				//std::cout << "(" << i << "," << j << "," << k << ")" << endl;
			}
		}
	}



	for (int a = 0; a < times; ++a) {
		int assort = 0;
		auto Cans(Canori);

		random_device engine;
		uniform_int_distribution<unsigned> dist1(0, size(Cans) - 1);
		int rand = dist1(engine);

		vector<int> answer;
		answer.push_back(Cans[rand].n0);
		answer.push_back(Cans[rand].n1);
		answer.push_back(Cans[rand].n2);

		std::cout << "Answer (" << answer[0] << "," << answer[1] << "," << answer[2] << ")" << endl;

		int k = 0;

		while (1) {
			vector<int> hint{ 0, 0 };
			uniform_int_distribution<unsigned> dist2(0, size(Cans) - 1);
			int rand1 = dist2(engine);
			vector<int> res;
			res.push_back(Cans[rand1].n0);
			res.push_back(Cans[rand1].n1);
			res.push_back(Cans[rand1].n2);

			hint = Hint(res, answer, hint);
			std::cout << "(" << res[0] << "," << res[1] << "," << res[2] << "), " << "(" << hint[0] << "," << hint[1] << ")" << endl;

			vector<int> imps;
			for (int i = 0; i < size(Cans); ++i) {
				vector<int> hint1{ 0, 0 };
				vector<int> cancopy{ Cans[i].n0, Cans[i].n1, Cans[i].n2 };
				hint1 = Hint(cancopy, res, hint1);
				if (hint[0] != hint1[0] || hint[1] != hint1[1]) {
					imps.push_back(i);
					//std::cout << i << "(" << Cans[i].n0 << "," << Cans[i].n1 << "," << Cans[i].n2 << "), " << "(" << hint1[0] << "," << hint1[1] << ")" << endl;
				}

			}
			//std::cout << size(imps) << endl;
			sort(imps.rbegin(), imps.rend());

			for (int i = 0; i < size(imps); ++i) {
				Cans.erase(Cans.begin() + imps[i]);
			}
			imps.clear();
			k++;
			if (hint[0] == 3) {
				std::cout << k << endl;
				

				switch (assort) {
				case 1:
					C00.nsum += k;
					//std::cout << C00.nsum << endl;
					break;
				case 2:
					C01.nsum += k;
					break;
				case 3:
					C02.nsum += k;
					break;
				case 4:
					C03.nsum += k;
					break;
				case 5:
					C10.nsum += k;
					break;
				case 6:
					C11.nsum += k;
					break;
				case 7:
					C12.nsum += k;
					break;
				case 8:
					C20.nsum += k;
					break;
				case 9:
					C30.nsum += k;
					break;
				}
				Cans.clear();
				break;
			}

			if (k == 1) {
				switch (hint[0]) {
				case 0:
					switch (hint[1]) {
					case 0:
						C00.count++;
						assort = 1;
						//std::cout << "OK" << C00.count << endl;
						break;
					case 1:
						C01.count++;
						assort = 2;
						//std::cout << "OK" << C01.count << endl;
						break;
					case 2:
						C02.count++;
						assort = 3;
						break;
					case 3:
						C03.count++;
						assort = 4;
						break;
					}
					break;
				case 1:
					switch (hint[1]) {
					case 0:
						C10.count++;
						assort = 5;
						break;
					case 1:
						C11.count++;
						assort = 6;
						break;
					case 2:
						C12.count++;
						assort = 7;
						break;
					}
					break;
				case 2:
					C20.count++;
					assort = 8;
					break;
				case 3:
					C30.count++;
					assort = 9;
					break;
				}
			}

		}
		sum += k;
	}
	std::cout << "Average is " << sum / times << endl;

	std::cout << "H00:" << C00.nsum / C00.count << endl;
	std::cout << "H01:" << C01.nsum / C01.count << endl;
	std::cout << "H02:" << C02.nsum / C02.count << endl;
	std::cout << "H03:" << C03.nsum / C03.count << endl;
	std::cout << "H10:" << C10.nsum / C10.count << endl;
	std::cout << "H11:" << C11.nsum / C11.count << endl;
	std::cout << "H12:" << C12.nsum / C12.count << endl;
	std::cout << "H20:" << C20.nsum / C20.count << endl;
	std::cout << "H30:" << C30.nsum / C30.count << endl;


	//人間用
	/*while (1) {
		vector<int> res(3);
		cin >> res[0];
		cin >> res[1];
		cin >> res[2];

		vector<int> hint{0, 0};

		if (res[0] == Answer[0]) {
			++hint[0];
		}
		if (res[1] == Answer[1]) {
			++hint[0];
		}
		if (res[2] == Answer[2]) {
			++hint[0];
		}

		for (int i = 0; i < 2; ++i) {
			int avoid = res[0];
			res.erase(res.begin());
			res.push_back(avoid);
			if (res[0] == Answer[0]) {
				++hint[1];
			}
			if (res[1] == Answer[1]) {
				++hint[1];
			}
			if (res[2] == Answer[2]) {
				++hint[1];
			}
		}

		std::cout << "(" << hint[0] << "," << hint[1] << ")" << endl;

		if (hint[0] == 3) break;

	}*/
	
	


}