#include <iostream>
#include <math.h>

using namespace std;

typedef struct dot
{
    int x;
    int y;
} dot;

float slope(dot a, dot b)
{
    if ((a.x - b.x) != 0)
        return ((float)a.y - (float)b.y) / ((float)a.x - (float)b.x);
    return INFINITY;
}

int is_par(float a, float b)
{
    if (a == INFINITY || a == -INFINITY)
    {
        if (b == 0 || b == -0)
            return 1;
    }
    else if (b == INFINITY || b == -INFINITY)
    {
        if (a == 0 || a == -0)
            return 1;
    }
    else if (a * b == -1)
    {
        return 1;
    }
    return 0;
}

int main()
{
    int n;
    cin >> n;
    dot arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i].x;
        cin >> arr[i].y;
    }
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == i)
                continue;

            for (int k = 0; k < n; k++)
            {
                if (k == i || k == j)
                    continue;
                float ij_s = slope(arr[i], arr[j]);
                // cout << ij_s << endl;
                float jk_s = slope(arr[j], arr[k]);
                // cout << jk_s << endl;
                if (is_par(ij_s, jk_s))
                {
                    count++;
                }
            }
        }
    }
    cout << count / 2;
}
