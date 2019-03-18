#include<iostream>
#include <cmath>
#include <vector>

struct point{
    double x = 0;
    double y = 0;
    
    point(){}
    point(double x, double y) : x(x), y(y){}
    
    point operator + (const point &a){
        point ret;
        ret.x = x + a.x;
        ret.y = y + a.y;
        return ret;
    }
    
    point operator - (const point &b){
        point zet;
        zet.x = x - b.x;
        zet.y = y - b.y;
        return zet;
    }
};

std::ostream &operator<<(std::ostream &os, point const &p){
    os << p.x;
    os << ",";
    os << p.y;
    return os;
}

auto Rotate(point p, double angle){
    double c = std::cos(1.5708);
    double s = std::sin(1.5708);
    
    auto new_x = c * p.x - s * p.y;
    auto new_y = s* p.x  + c * p.y;
    
    point new_point(new_x, new_y);
    
    return new_point;
}

int main(){
    
    double xStart1 = 90, yStart1 = 110, userX, userY, columnGap = 3;
    
    std::cout << "Enter X coordinate by MM: ";
    //std::cin >> userX;
    userX = 30;
    
    std::vector<point> layer;
    
    userY = userX;
    
    for(int i = 0; i <= (userX / columnGap); i++){

        if(i == 0){
            layer.push_back(point(xStart1, yStart1));
        }

        else{
            for(int j = 0; j < 2; j++){
                if(i % 2 == 0){
                    if(j % 2 == 0){
                        layer.push_back(point(xStart1, yStart1));
                    }
                    else{
                        xStart1 += columnGap;
                        layer.push_back(point(xStart1, yStart1));
                    }
                }
                else{
                    if(j % 2 == 0){
                        layer.push_back(point(xStart1, yStart1 - userY));
                    }
                    else{
                        xStart1 += columnGap;
                        layer.push_back(point(xStart1, yStart1 - userY));
                    }
                }
            }
        }
    }
    
    layer.pop_back();
    
    
    auto [minX, maxX] = std::minmax_element(begin(layer), end(layer),
                                    [&](const point& a, const point& b) { return a.x < b.x; });

    auto [minY, maxY] = std::minmax_element(begin(layer), end(layer),
                                    [&](const point& a, const point& b) { return a.y < b.y; });

    
    std::cout << "\nminx = " << *minX << ", maxx = " << *maxX << '\n' << std::endl;
    std::cout << "miny = " << *minY << ", maxy = " << *maxY << '\n' << std::endl;
    
    auto xCenter = ((*minX).x + (*maxX).x) / 2;
    auto yCenter = ((*minY).y + (*maxY).y) / 2;
    
    point r_center(xCenter, yCenter);
    
    std::cout << r_center << std::endl;
    
    std::vector<point> copyLayer(layer.size());
    
    //for (int i = 0; i <10; i++) {
    
    for(auto const & p: layer){
        std::cout << "G1 X" <<p.x << " Y" << p.y << std::endl;
    }

    std::transform(layer.begin(), layer.end(), copyLayer.begin(),
                   [&](point x) -> auto {
                       auto r_loc = x - r_center;
                       auto r_rot = Rotate(r_loc, -90);
                       return r_center + r_rot;
                   });
    
    std::reverse(copyLayer.begin(), copyLayer.end());
        
    
    for(auto const & p: copyLayer){
        std::cout << "G1 X" <<p.x << " Y" << p.y << std::endl;
    }
    
    //}
    
    return 0;
}
