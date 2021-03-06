#ifndef COMPUTE_DMAP_HH
#define COMPUTE_DMAP_HH

#include <queue>
#include <limits>
#include "tools/Image2D.hh"

namespace my {

    Image2D<unsigned>
    compute_dmap__SPECIFIC(const Image2D<bool_t>& input) {
        Box2D D = input.domain();

        const unsigned max = std::numeric_limits<unsigned>::max();
        Image2D<unsigned> dmap(D);

        Box2DIterator p(D);
        for (p.start() ; p.is_valid() ; p.next()) {
            dmap(p) = max;
        }

        std::queue<Point2D> q;
        Neighb2DIterator n;

        for_all(p) {
            if (input(p) == true) {
                dmap(p) = 0;
                n.center_at(p);
                for (n.start() ; n.is_valid() ; n.next()) {
                    if (D.has(n) && input(n) == false) {
                        q.push(p);
                        break;
                    }
                }
            }
        }

        while (!q.empty()) {
            Point2D p = q.front();
            q.pop();
            n.center_at(p);
            for_all(n) {
                if (D.has(n) && dmap(n) == max) {
                    dmap(n) = dmap(p) + 1;
                    q.push(n);
                }
            }
        }

        return dmap;
    }

    template <typename I>
    typename I::template with_value_type<unsigned>::ret
    compute_dmap__GENERIC(const Image<I>& input_) {
        typedef typename I::point_type point_type;
        typedef typename I::template with_value_type<unsigned>::ret dmap_type;

        const I& input = input_.exact();
        auto D = input.domain();

        const unsigned max = std::numeric_limits<unsigned>::max();
        dmap_type dmap(D);

        auto p = input.pIterator();
        for_all(p) {
            dmap(p) = max;
        }

        std::queue<point_type> q;
        auto n = input.nIterator();

        for_all(p) {
            if (input(p) == true) {
                dmap(p) = 0;
                n.center_at(p);
                for_all(n) {
                    if (D.has(n) && input(n) == false) {
                        q.push(p);
                        break;
                    }
                }
            }
        }

        while (!q.empty()) {
            point_type p = q.front();
            q.pop();
            n.center_at(p);
            for_all(n) {
                if (D.has(n) && dmap(n) == max) {
                    dmap(n) = dmap(p) + 1;
                    q.push(n);
                }
            }
        }

        return dmap;
    }

} // end of namespace my

#endif // COMPUTE_DMAP_HH
