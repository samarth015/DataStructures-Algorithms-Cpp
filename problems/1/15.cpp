/*

	Deﬁne a Rectangle class that provides getLength and getWidth . Using the findMax
	routines in Figure 1.25, write a main that creates an array of Rectangle and ﬁnds the
	largest Rectangle ﬁrst on the basis of area and then on the basis of perimeter.

*/

//Answer

#include <iostream>
#include <vector>

class Rectangle{
	private: 
		std::size_t length, width;
	public:
		Rectangle(std::size_t len, std::size_t wid): length{len}, width{wid} {} 

		std::size_t getLength() const{
			return length;
		}
		std::size_t getWidth() const{
			return width;
		}

		void print() const{
			std::cout << length << " " << width << std::endl;
		}
};

template<typename Object, typename Comparator>
const Object& findMax(const std::vector<Object> & arr, Comparator isLessThan )
{
	int maxIndex = 0;
	for( int i = 1; i < arr.size( ); ++i )
		if( isLessThan( arr[ maxIndex ], arr[ i ] ) )
			maxIndex = i;
	return arr[ maxIndex ];
}

class AreaCompare{
	public:
	bool operator() (const Rectangle& a, const Rectangle& b) const{
		return a.getLength()*a.getWidth() < b.getLength()*b.getWidth();
	}
};

class PerimeterCompare{
	public:
	bool operator() (const Rectangle& a, const Rectangle& b) const{
		return a.getLength()+a.getWidth() < b.getLength()+b.getWidth();
	}
};


int main() {
	std::vector<Rectangle> recv {{10,2},{2,6},{3,4},{5,5},{9,1},{8,3},{7,3}};

	for(auto& rec : recv) rec.print();

	std::cout << "Largest Area : "; 
	findMax<Rectangle>(recv, AreaCompare{}).print(); 
	std::cout << "Largest Perimeter : "; 
	findMax<Rectangle>(recv, PerimeterCompare{}).print(); 
}
