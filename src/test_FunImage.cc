#include "tools/FunImage.hh"
#include "tools/Image2D.hh"
#include "tools/compute_dmap.hh"
#include "tools/compute_dmap__v2.hh"

int main() {
    using namespace my;

    Image2D<int> ima(2,2);
    debug_iota(ima);
    ima.debug_print();

    std::cout << "ima  = " << ima << std::endl;
    std::cout << "ima' = " << make_FunImage(ima, equals(1)) << std::endl;

    Image2D<unsigned> dmap = compute_dmap__GENERIC(
        make_FunImage(ima, equals(1))
    );
    dmap.debug_print();
}
