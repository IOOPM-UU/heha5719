#include <stdio.h>

typedef struct point point_t;

struct point {
    int x;
    int y;
};

point_t p = { .x = 10, .y = -42};

void translate(point_t *p1, point_t *p2)
{
  p1->x += p2->x;
  p1->y += p2->y;
}

//Inkopierat

void print_point(point_t *p) {
    printf("point(x : %d, y : %d)\n", p->x, p->y);
}

point_t make_point(int a, int b) {
    point_t p3 = {.x = a, .y = b};
    return p3;
}

typedef struct rectangle rectangle_t;

struct rectangle {
    point_t upper_left;
    point_t lower_right;
};

void print_rect(rectangle_t *pekare) {
    printf("Rectangle(upper_left = ");
    print_point(&pekare -> upper_left);
    printf("lower_left ");
    print_point(&pekare -> lower_right);
}

rectangle_t make_rect(int a, int b, int c, int d) {
    rectangle_t ny_rektangel = {.upper_left = {.x = a, .y = b}, .lower_right = {.x = c, .y = d}};
    return ny_rektangel; //eller kör bara ny_rektangel som den är
}

int area_rect(rectangle_t *pointer) {
    int y2 = pointer -> upper_left.y; 
    int y1 = pointer -> lower_right.y;
    int x2 = pointer -> lower_right.x;
    int x1 = pointer -> upper_left.x;
    int y_tot = y2 - y1;
    int x_tot = x2 - x1;
    int area = x_tot * y_tot;
    return area;
}

void main(void) {

}

/*  make_rect
    rectangle_t r = make_rect(1, 2, 20, 21);
    print_rect(&r);
*/
/*  area_rect
    rectangle_t r = {.upper_left = {.x = 20, .y = 20}, .lower_right = {.x = 40, .y = 10}};
    printf("%d\n", area_rect(&r));
*/
/*  print_rect
    rectangle_t r = {.upper_left = {.x = 20, .y = 10}, .lower_right = {.x = 30, .y = 10}};
    print_rect(&r);
*/