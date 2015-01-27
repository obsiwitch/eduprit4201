#ifndef COMPUTE_DMAP__V2_HH
#define COMPUTE_DMAP__V2_HH

#include <queue>
#include "tools/Image.hh"

namespace my {

    template <typename I, typename F>
    typename I::template with_value_type<unsigned>::ret
    compute_dmap__v2(const Image<I>& input_, F& f) {
        typedef typename I::point_type point_type;
        typedef typename I::template with_value_type<unsigned>::ret dmap_type;

        const I& input = input_.exact();
        auto D = input.domain();

        const unsigned max = -1;
        dmap_type dmap(D);

        auto p = dmap.pIterator();
        for_all(p) {
            dmap(p) = max;
        }

        std::queue<point_type> q;
        auto n = dmap.nIterator();

        for_all(p){
            if (input(p) != 0) {
                // FIXME: cut
            }
        }

        while (!q.empty()) {
            point_type p = q.front();
            q.pop();
            n.center_at(p);
            for_all(n) {
                if (D.has(n) && dmap(n) == max) {
                    // FIXME: cut
                }
            }
        }

        return dmap;
    }

    // FIXME: cut

} // end of namespace my

#endif // COMPUTE_DMAP__V2_HH
