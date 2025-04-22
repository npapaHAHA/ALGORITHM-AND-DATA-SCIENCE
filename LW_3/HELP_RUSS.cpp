#include <iostream>

bool place_compability(int cords_of_place[], int min_distance, int n, int k) {
    int count = 1, place_of_last = cords_of_place[0];

    for (int i = 0; i < n; i++) {
        int distance_between = cords_of_place[i] - place_of_last;

        if (distance_between >= min_distance) {

            count++;
            place_of_last = cords_of_place[i];
        }
    }

    if (count >= k) {
        return true;
    }
    else {
        return false;

    }
}

int bin_search(int cords_of_place[], int n, int k) {

    int left_lim_of_dist = 0, rights_lim_of_dist = cords_of_place[n - 1] - cords_of_place[0];
    while (rights_lim_of_dist - 1 > left_lim_of_dist) {
        int mid_pos = (rights_lim_of_dist + left_lim_of_dist) / 2;

        if ((place_compability(cords_of_place, mid_pos, n, k)) == true) {
            left_lim_of_dist = mid_pos;

        }
        else {
            rights_lim_of_dist = mid_pos;
        }
    }
    return  left_lim_of_dist;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    int cords_of_place[n];

    for (int i = 0; i < n; i++) {

        std::cin >> cords_of_place[i];
    }

    int res = bin_search(cords_of_place, n, k);
    std::cout << res;
}