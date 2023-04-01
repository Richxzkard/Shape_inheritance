#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef double (*VirtualMethodPointer)(void *);
typedef VirtualMethodPointer * VTableType;

//shape class work here~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

typedef struct{
    VTableType VPointer;
    char name[20];
}Shape;

double Shape_area(Shape *_this){
    return 0.0;
}

void Shape_draw(Shape * _this){
    printf("Shape.draw() You should never see this.");
}

VirtualMethodPointer Shape_VTable [] = {
    (VirtualMethodPointer)Shape_area,
    (VirtualMethodPointer)Shape_draw
};

Shape* Shape_Shape(Shape* _this, char* newName){
    _this->VPointer = Shape_VTable;
    strcpy(_this->name, newName);
    return _this;
}

//Triangle class here~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

typedef struct{
    VTableType Vpointer;
    char name[20];
    double height;
    double base;
}Triangle;

double Triangle_area(Triangle* _this){
    return _this->height * _this->base * 1/2;
}

void Triangle_draw(Triangle* _this){
    printf("%s(%.0f, %.0f) : %.2f\n", _this->name, _this->height, _this->base, Triangle_area(_this));
    printf("   *\n");
	printf("  * *\n");
	printf(" *   *\n");
	printf("*******\n");
}

VirtualMethodPointer Triangle_VTable [] = {
    (VirtualMethodPointer)Triangle_area,
    (VirtualMethodPointer)Triangle_draw
};

Triangle* Triangle_Triangle(Triangle* _this, char *newName, double newHeight, double newBase){
    Shape_Shape((Shape *)_this, newName);
    _this->Vpointer = Triangle_VTable;
    _this->height = newHeight;
    _this->base = newBase;
    return _this;
}

//Circle class here~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define PI 3.14159

typedef struct{
    VTableType Vpointer;
    char name[20];
    double radius;
}Circle;

double Circle_area(Circle* _this){
    return _this->radius * _this->radius * PI;
}

void Circle_draw(Circle* _this){
    printf("%s(%.0f) : %.2f\n", _this->name, _this->radius, Circle_area(_this));
    printf("   ****\n");
	printf(" *      *\n");
	printf("*        *\n");
	printf("*        *\n");
	printf(" *      *\n");
	printf("   ****\n");
}

VirtualMethodPointer Circle_VTable [] = {
    (VirtualMethodPointer)Circle_area,
    (VirtualMethodPointer)Circle_draw
};

Circle* Circle_Circle(Circle* _this, char *newName, double newRadius){
    Shape_Shape((Shape *)_this, newName);
    _this->Vpointer = Circle_VTable;
    _this->radius = newRadius;
    return _this;
}

//Square class here~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
typedef struct{
    VTableType Vpointer;
    char name[20];
    double length;
}Square;

double Square_area(Square* _this){
    return _this->length * _this->length;
}

void Square_draw(Square* _this){
    printf("%s(%.0f) : %.0f\n", _this->name, _this->length, Square_area(_this));
    printf("*******\n");
	printf("*     *\n");
	printf("*     *\n");
	printf("*     *\n");
	printf("*     *\n");
	printf("*     *\n");
	printf("*******\n");
}

VirtualMethodPointer Square_VTable [] = {
    (VirtualMethodPointer)Square_area,
    (VirtualMethodPointer)Square_draw
};

Square* Square_Square(Square* _this, char *newName, double newLength){
    Shape_Shape((Shape *)_this, newName);
    _this->Vpointer = Square_VTable;
    _this->length = newLength;
    return _this;
}

//Rectangle class here~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
typedef struct{
    VTableType Vpointer;
    char name[20];
    double length;
    double width;
}Rectangle;

double Rectangle_area(Rectangle* _this){
    return _this->length * _this->width;
}

void Rectangle_draw(Rectangle* _this){
    printf("%s(%.0f, %.0f) : %.0f\n", _this->name, _this->length, _this->width, Rectangle_area(_this));
    printf("*******\n");
	printf("*     *\n");
	printf("*     *\n");
	printf("*******\n");
}

VirtualMethodPointer Rectangle_VTable [] = {
    (VirtualMethodPointer)Rectangle_area,
    (VirtualMethodPointer)Rectangle_draw
};

Rectangle* Rectangle_Rectangle(Rectangle* _this, char *newName, double newLength, double newWidth){
    Square_Square((Square *)_this, newName, newLength);
    _this->Vpointer = Rectangle_VTable;
    _this->width = newWidth;
    return _this;
}

//Congratulations you finished class shit~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main(){
    double total = 0.0;

    Shape * AhhhhhhhImGonnaDie [] = {
        (Shape *)Triangle_Triangle((Triangle *)malloc(sizeof(Triangle)), "FirstTriangle", 12.0, 15.0),
        (Shape *)Triangle_Triangle((Triangle *)malloc(sizeof(Triangle)), "SecondTriangle", 11.0, 14.0),

        (Shape *)Circle_Circle((Circle *)malloc(sizeof(Circle)), "FirstCircle", 12.0),
        (Shape *)Circle_Circle((Circle *)malloc(sizeof(Circle)), "SecondCircle", 11.0),

        (Shape *)Square_Square((Square *)malloc(sizeof(Square)), "FirstSquare", 12.0),
        (Shape *)Square_Square((Square *)malloc(sizeof(Square)), "SecondSquare", 11.0),

        (Shape *)Rectangle_Rectangle((Rectangle *)malloc(sizeof(Rectangle)), "FirstRectangle", 12.0, 15.0),
        (Shape *)Rectangle_Rectangle((Rectangle *)malloc(sizeof(Rectangle)), "SecondRectangle", 11.0, 14.0)
    };

    for (int i=0; i<sizeof(AhhhhhhhImGonnaDie)/sizeof(*AhhhhhhhImGonnaDie); i++){
        (AhhhhhhhImGonnaDie[i]->VPointer[1])(AhhhhhhhImGonnaDie[i]);
        total += (AhhhhhhhImGonnaDie[i]->VPointer[0])(AhhhhhhhImGonnaDie[i]);
    }

    printf("Total : %.2f", total);
}