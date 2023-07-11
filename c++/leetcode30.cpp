class Solution {
    private:
        map<string, int> string_num_map;
        map<string, int> string_num_map_temp;

        void insertMap(string& word) {
            auto itr = string_num_map.find(word);
            if (itr != string_num_map.end()) {
                itr->second++;
            } else {
                string_num_map[word] = 1;
            }
            string_num_map_temp[word] = 0;
            this.all++;
        }
        void buildMap(vector<string>& words) {
            for_each(words.begin(); words.end(); insertMap);
        }

        int flag = 1; // 1 +; 0 -
        int length = 0;
        int all = 0;
        // 1 正确 0 失败
        int checkWords(string& s, int idx) {
            int num = 0;
            string temp;
            int ret = 0;
            for (int i = idx; i < s.size() && (i + this.length) < s.size(); i += this.length) {
                temp = string(s, i, this.length);
                auto itr = string_num_map.find(word);
                if (itr != string_num_map.end()) {
                    auto itr_temp = string_num_map_temp.find(word);
                    if (this.flag) {
                        // 正向计算
                        if (itr_temp.second() < 0) {
                            itr_temp.second = 0;
                        }
                        itr_temp.second++;
                        num++;
                        if (itr_temp.second() > itr.second()) {
                            break;
                        }
                    } else {
                        // 反向计算
                        if (itr_temp.second() > 0) {
                            itr_temp.second = 0;
                        }
                        num++;
                        itr_temp.second--;
                        if (-itr_temp.second() > itr.second()) {
                            break;
                        }
                    }
                    if (all == num) {
                        ret = 1;
                        break;
                    }
                } else {
                    break;
                }
            }
            this.flag = this.flag?0:1;
            return ret;
        }

    public:
        vector<int> findSubstring(string s, vector<string>& words) {
            this.length = words[0].size();
            buildMap(words);
            vector<int> ret;
            for (int idx = 0; idx < s.size() - this.length; idx++) {
                if (checkWords(s, idx)) {
                    ret.push_back(idx);
                }
            }
            return ret;
        }
};
