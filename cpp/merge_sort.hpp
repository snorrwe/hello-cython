#pragma once
#include <algorithm>
#include <iterator>
#include <vector>

namespace merge_sort {

template <typename It>
class MergeSortImpl;

template <typename It>
void sort(It begin, It end)
{
    using category = typename std::iterator_traits<It>::iterator_category;
    auto sorter = MergeSortImpl<It> { begin, end, category() };
    sorter.sort();
}

template <typename It>
class MergeSortImpl {
    using TValue = typename std::iterator_traits<It>::value_type;
    using Container = std::vector<TValue>;

    It begin;
    It end;
    Container container_a;
    Container container_b;

public:
    MergeSortImpl(It begin, It end, std::random_access_iterator_tag)
        : begin(begin)
        , end(end)
    {
    }

    void sort()
    {
        const auto size = end - begin;

        auto init = [&](auto& container) {
            container.reserve(size);
            container.clear();
            std::copy(begin, end, std::back_inserter(container));
        };

        init(container_a);
        init(container_b);

        top_down_split_merge(container_b, 0, size, container_a);

        // Copy the result back to the original range
        std::copy(container_a.begin(), container_a.end(), begin);
    }

private:
    static void top_down_split_merge(Container& container_b, size_t begin, size_t end,
        Container& container_a)
    {
        // If length is less than 2 consider the range sorted
        if (end - begin < 2)
            return;

        auto mid = (end + begin) / 2;

        // Swap the containers on every level of the recursion
        top_down_split_merge(container_a, begin, mid, container_b);
        top_down_split_merge(container_a, mid, end, container_b);

        // Call merge with the original order of the containers
        merge(container_b, begin, mid, end, container_a);
    }

    static void merge(Container& container_a, size_t begin, size_t mid, size_t end,
        Container& container_b)
    {
        auto i = begin, j = mid;
        for (; begin < end; ++begin) {
            if (i < mid && (j >= end || container_a[i] <= container_a[j])) {
                container_b[begin] = container_a[i];
                ++i;
            } else {
                container_b[begin] = container_a[j];
                ++j;
            }
        }
    }
};

} // namespace merge_sort

