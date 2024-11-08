std::vector<std::vector<int>> stableMarriage(std::vector<std::vector<int>> first, std::vector<std::vector<int>> second, std::vector<int> cap) {
	assert(cap.size() == second.size());
	int n = (int) first.size(), m = (int) second.size();
	// init
	// if O(N * M) first in memory, use table
	std::map<std::pair<int, int>, int> prio;
	std::vector<std::set<std::pair<int, int>>> current(m);
	for(int i = 0; i < n; i++) {
		std::reverse(first[i].begin(), first[i].end());
	}
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < (int) second[i].size(); j++) {
			prio[{second[i][j], i}] = j;
		}
	}
	// solve
	for(int i = 0; i < n; i++) {
		int on = i;
		while(!first[on].empty()) {
			int to = first[on].back();
			first[on].pop_back();
			if(cap[to]) {
				cap[to]--;
				assert(prio.count({on, to}));
				current[to].insert({prio[{on, to}], on});
				break;
			}
			assert(!current[to].empty());
			auto it = current[to].end();
			it--;
			if(it->first > prio[{on, to}]) {
				int nxt = it->second;
				current[to].erase(it);
				current[to].insert({prio[{on, to}], on});
				on = nxt;
			}
		}
	}
	// return
	std::vector<std::vector<int>> ans(m);
	for(int i = 0; i < m; i++) {
		for(auto it : current[i]) {
			ans[i].push_back(it.second);
		}
	}
	return ans;
}