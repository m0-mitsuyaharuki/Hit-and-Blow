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

int main() {

	vector<Candidate> Cans; //候補プール

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
	uniform_int_distribution<unsigned> dist1(0, size(Cans)-1);
	int rand = dist1(engine);

	vector<int> Answer;
	Answer.push_back(Cans[rand].n0);
	Answer.push_back(Cans[rand].n1);
	Answer.push_back(Cans[rand].n2);

	/*Answer.push_back(Cans[0].n0);
	Answer.push_back(Cans[0].n1);
	Answer.push_back(Cans[0].n2);*/

	std::cout << "(" << Answer[0] << "," << Answer[1] << "," << Answer[2] << ")" << endl;

	vector<int> hint{0, 0};

	//=====================================
	//ここから
	uniform_int_distribution<unsigned> dist1(0, size(Cans) - 1);
	int rand1 = dist1(engine);
	vector<int> res;
	res.push_back(Cans[rand1].n0);
	res.push_back(Cans[rand1].n1);
	res.push_back(Cans[rand1].n2);
	//auto rescopy(res);

	if (res[0] == Answer[0]) ++hint[0];
	if (res[1] == Answer[1]) ++hint[0];
	if (res[2] == Answer[2]) ++hint[0];
	for (int i = 0; i < 2; ++i) {
		int avoid = res[0];
		res.erase(res.begin());
		res.push_back(avoid);
		if (res[0] == Answer[0]) ++hint[1];
		if (res[1] == Answer[1]) ++hint[1];
		if (res[2] == Answer[2]) ++hint[1];
	}
	std::cout << "(" << hint[0] << "," << hint[1] << ")" << endl;

	int avoid = res[0];
	res.erase(res.begin());
	res.push_back(avoid);

	vector<int> imps;
	for (int i = 0; i < size(Cans); ++i) {
		if (res[0] == Cans[i].n0) ++hint[0];
		if (res[1] == Cans[i].n1) ++hint[0];
		if (res[2] == Cans[i].n2) ++hint[0];
		for (int i = 0; i < 2; ++i) {
			int avoid = res[0];
			res.erase(res.begin());
			res.push_back(avoid);
			if (res[0] == Cans[i].n0) ++hint[1];
			if (res[1] == Cans[i].n1) ++hint[1];
			if (res[2] == Cans[i].n2) ++hint[1];
		}
		imps.push_back(i);
	}
	sort(imps.begin(), imps.end());

	for (int i = 0; i < size(imps); ++i) {
		Cans.erase(Cans.begin()+imps[i]);
	}
	//ここまでをwhile文にぶち込めばおけ
	//================================

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