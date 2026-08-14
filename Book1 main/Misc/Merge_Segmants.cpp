
    vector <pair<int,int>> ranges;
    vector<int> left , right;
    sort(ranges.begin() , ranges.end());
    int st = ranges[0].first , en = ranges[0].second;
    for(int i = 1;i < ranges.size(); i++){
        if(ranges[i].first < en)
            en = max(en , ranges[i].second);
        else{
            left.push_back(st);
            right.push_back(en);
            st = ranges[i].first;
            en = ranges[i].second;
        }
    }
    left.push_back(st);
    right.push_back(en);
    int m = left.size();
