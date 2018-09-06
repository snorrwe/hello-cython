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
    Container A;
    Container B;

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
            std::copy(begin, end, std::back_inserter(container));
        };

        init(A);
        init(B);

        top_down_split_merge(B, 0, size, A);

        // Copy the result back to the original range
        std::copy(A.begin(), A.end(), begin);
    }

private:
    static void top_down_split_merge(Container& B, size_t begin, size_t end,
        Container& A)
    {
        // If length is less than 2 consider the range sorted
        if (end - begin < 2)
            return;

        auto mid = (end + begin) / 2;

        top_down_split_merge(A, begin, mid, B);
        top_down_split_merge(A, mid, end, B);

        merge(B, begin, mid, end, A);
    }

    static void merge(Container& A, size_t begin, size_t mid, size_t end,
        Container& B)
    {
        auto i = begin, j = mid;
        for (; begin < end; ++begin) {
            if (i < mid && (j >= end || A[i] <= A[j])) {
                B[begin] = A[i];
                ++i;
            } else {
                B[begin] = A[j];
                ++j;
            }
        }
    }
};

} // namespace merge_sort

