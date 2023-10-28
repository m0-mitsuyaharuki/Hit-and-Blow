#include <iostream>
#include <vector>
#include <random>
#include <algorithm>	
using namespace std;

struct Candidate { //数字の組の中身
	int n0 = 0, n1 = 0, n2 = 0;
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
	//std::cout << "(" << comp1[0] << ",," << comp1[1] << "," << comp1[2] << "), " << "(" << hint[0] << "," << hint[1] << ")" << endl;
}

int main() {

	vector<Candidate> Cans; //候補プール

	float sum = 0;
	const int times = 100;

	for (int a = 0; a < times; ++a) {


		//候補プールを作成
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 10; ++j) {
				if (i == j) {
					continue;
				}
				for (int k = 0; k < 10; ++k) {
					if (i == k || j == k) {
						continue;
					}
					MakeCan(i, j, k, Cans);
					//std::cout << "(" << i << "," << j << "," << k << ")" << endl;
				}
			}
		}

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
			std::cout << "(" << res[0] << ",," << res[1] << "," << res[2] << "), " << "(" << hint[0] << "," << hint[1] << ")" << endl;

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
				//std::cout << "(" << Answer[0] << "," << Answer[1] << "," << Answer[2] << ")" << endl;
				std::cout << k << endl;
				Cans.clear();
				break;
			}
		}
		sum += k;
	}
	std::cout << "Average is " << sum / times << endl;

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