template <typename T>
void counting_sort(std::vector <my_class <T> > &data){
    std::vector <int> ones_ind;
    std::vector <int> zeros_ind;

    for (int i = 0; i < data.size(); i++)
        if (data[i].key)
            ones_ind.push_back(i);
        else
            zeros_ind.push_back(i);

}

template <typename T>
void bubble_sort(std::vector <my_class <T> > &data){
    for (int i = int(data.size()) - 1; i > 0; i--){
        bool flag = false;

        for (int j = 0; j < i; j++)
            if (data[j].key > data[j + 1].key)
                std::swap(data[j], data[j + 1]);

        if (!flag) break;
    }
}

template <typename T>
void swap_sort(std::vector <my_class <T> > &data){
    int from = 0, to = int(data.size()) - 1;

    while (from < to){
        while(from < to && !data[from].key)
            from++;
        while(from < to && data[to].key)
            to--;
        std::swap(data[from], data[to]);
    }
}