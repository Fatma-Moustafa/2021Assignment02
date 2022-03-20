#include <algorithm>
#include <random>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

/*
 * Struct for representing a point.
 Since we are dealing with a 2D tree we define x and y coordinates.
 They are defined as private, but public functions are used to call them.
 */
struct Point {
private:
    double x;
    double y;

public:
    //constructors for the point struct
    Point() = default;
    Point(double x, double y) : x{ x }, y{ y } {}
    double getX() const { return x; }
    double getY() const { return y; }
};

//operator overloading for <<
std::ostream& operator<<(std::ostream& out, Point& point)
{
    return out << "Point (" << point.getX() << ", " << point.getY() << ")";
}

struct Node {
private:
    Point split; // splitting node
    Node* left;
    Node* right;

public:
    Node() = default;
    Node(Point split) : split{ split }, left{ nullptr }, right{ nullptr } {}

    Node* getLeft() { return left; }
    Node* getRight() { return right; }
    void setLeft(Node* _left) { left = _left; }
    void setRight(Node* _right) { right = _right; }
    Point getPoint() { return split; }


};

template <typename Iterator>
void print(Iterator first, Iterator last)
{
    for (auto it = first; it != last; ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n\n\n";
}

template <typename Iterator>
Point splitpoint(Iterator first, Iterator median, Iterator last, int axis)
{
    if (axis == 0) {
        std::nth_element(first, median, last,
            [](const Point& point1, const Point& point2) {
                return point1.getX() < point2.getX();
            }
        );
    }
    else {
        std::nth_element(first, median, last,
            [](const Point& point1, const Point& point2) {
                return point1.getY() < point2.getY();
            }
        );
    }

    return *median;
}

Node* buildSerialTree(std::vector<Point>& points, int first, int last, int dim, int axis) {

    if (last - first <= 0) {
        Node* node = new Node(points[first]);
        node->setLeft(nullptr);
        node->setRight(nullptr);
        return node;
    }

    int median = (first + last) / 2;

    Point split = chooseSplit(points.begin() + first, points.begin() + median, points.begin() + last, axis);

    Node* node = new Node(split);

    int current_axis = (axis + 1) % dim ; // to cycle through x and y axis

    node->setLeft(buildSerialTree(points, first, median, dim, current_axis));

    node->setRight(buildSerialTree(points, median + 1, last, dim, current_axis));

    return node;
}




int main(int argc, char* argv[]) {

    int exponent = 8;
    std::vector<Point>  pts{};

    int m = pow(10, exponent);

    for (int i = 0; i < m; i++) {
        srand(i);
        double x = double(rand()) / double(RAND_MAX);
        srand(i + 10);
        double y = double(rand()) / double(RAND_MAX);
        pts.push_back({ x,y });
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;

    start = std::chrono::high_resolution_clock::now();

    Node* n = buildSerialTree(pts, 0, pts.size() - 1, 2, 0);

    end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = end - start;
    std::cout << "Time of Serial computation: " << diff.count() << " (s)" << std::endl;
    return 0;
}