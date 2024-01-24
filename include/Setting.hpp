#ifndef _SETTING_
#define _SETTING_
/*the number of nodes in each x and y directions*/
inline constexpr unsigned int Xnode = 2048;
/*the number of nodes in each x and y directions*/
inline constexpr unsigned int Ynode = Xnode;

/*the number of nodes in each x and y directions*/
inline constexpr double Q = 1.0;

/*the range of the problem*/
inline constexpr double R = 1.0;

/*space step*/
inline constexpr double h = R / (Xnode - 1);

/*the 2D pointer used to store the Martix*/
inline double** A = nullptr;

/*the 1D pointer used to store the vector x*/
inline double* x = nullptr;
inline double* x_all = nullptr;

/*the 1D pointer used to store the vector b*/
inline double* b = nullptr;

#endif
