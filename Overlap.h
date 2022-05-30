#include <iostream>
#include <vector>

struct Place;
class Overlap{
    public:
        virtual void handleOverlaps(std::vector<Place> data);
};

class OddOverlap : public Overlap{
    public:
        void handleOverlaps(std::vector<Place> data);
};

class EvenOverlap : public Overlap{
    public:
        void handleOverlaps(std::vector<Place> data);
};