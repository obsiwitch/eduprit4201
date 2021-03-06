#include "tools/Image2D.hh"

namespace my {

    /**
     * Simple algorithm, 1st version
     */
    template <typename I>
    void a_simple_algorithm__v1(const Image<I>& ima_) {
        const I& ima = ima_.exact();

        auto p = ima.pIterator();
        for_all(p) {
            std::cout << ima(p) << ' ';
        }

        std::cout << std::endl;
    }

    /**
     * Simle algorithme 2nd version
     * It can now be modified externally thanks to f.
     */
    template <typename I, typename F>
    void a_simple_algorithm__v2(const Image<I>& ima_, F& f) {
        const I& ima = ima_.exact();
        f.init(); // do something at initialization

        auto p = ima.pIterator();
        for_all(p) {
            std::cout << ima(p) << ' ';
            f.process(p); // do something at p
        }

        std::cout << std::endl;
        f.final(); // do something finally
    }

    struct nada {
        void init() {}
        void process(const Point2D&) {}
        void final() {}
    };

    template <typename I>
    void a_simple_algorithm__v2(const Image<I>& ima_) {
        nada f;
        a_simple_algorithm__v2(ima_, f);
    }

    struct print_p {
        void init() {}

        void process(const Point2D& p) {
            std::cout << p << ' ';
        }

        void final() {}
    };

    struct counter {
        unsigned value;

        counter() {
            value = 0;
        }

        void init() {
            std::cout << "I'm gonna count..." << std::endl;
        }

        void process(const Point2D&) {
            value += 1;
        }

        void final() {
            std::cout << "Result: " << value << " iterations." << std::endl;
        }
    };

} // end of namespace my

int main() {
    using namespace my;

    Image2D<unsigned> ima(2, 3);
    debug_iota(ima);


    std::cout << "v1: ";
    a_simple_algorithm__v1(ima);


    std::cout << std::endl << "v2: ";
    a_simple_algorithm__v2(ima);  // equivalent as above


    std::cout << std::endl << "v2 with print_p: ";
    print_p f1;
    a_simple_algorithm__v2(ima, f1);


    std::cout << std::endl << "v2 with a counter: " << std::endl;
    counter f2;
    a_simple_algorithm__v2(ima, f2);
}
