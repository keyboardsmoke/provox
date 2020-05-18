#pragma once

// X = cols
// Y = rows
template<typename T, size_t Cols, size_t Rows>
class Matrix
{
    typedef Matrix<T, Cols, Rows> MatrixType;

public:
    Matrix() : m_data { static_cast<T>(0) } {}

    // See:
    // https://github.com/Kode/Kinc/blob/master/Sources/Kore/Math/Matrix.h#L112

    static MatrixType Identity()
    {
        MatrixType m;
        
        for (size_t x = 0; x < Cols; ++x)
        {
            m.Set(x, x, static_cast<T>(1));
        }

        return m;
    }

    static MatrixType OrthogonalProjection(T left, T right, T bottom, T top, T zn, T zf)
    {
        T tx = -(right + left) / (right - left);
        T ty = -(top + bottom) / (top - bottom);
        T tz = -(zf + zn) / (zf - zn);

        MatrixType m = Identity();
        m.Set(0, 0, static_cast<T>(2) / (right - left));
        m.Set(1, 0, static_cast<T>(0));
        m.Set(2, 0, static_cast<T>(0));
        m.Set(3, 0, static_cast<T>(0));
        m.Set(0, 1, static_cast<T>(0));
        m.Set(1, 1, static_cast<T>(2) / (top - bottom));
        m.Set(2, 1, static_cast<T>(0));
        m.Set(3, 1, static_cast<T>(0));
        m.Set(0, 2, static_cast<T>(0));
        m.Set(1, 2, static_cast<T>(0));
        m.Set(2, 2, static_cast<T>(-2) / (zf - zn));
        m.Set(3, 2, static_cast<T>(0));
        m.Set(0, 3, tx);
        m.Set(1, 3, ty);
        m.Set(2, 3, tz);
        m.Set(3, 3, static_cast<T>(1));
        return m;
    }

    static MatrixType Perspective(T left, T right, T top, T bottom, T zn, T zf)
    {
        MatrixType m;
        m.Set(0, 0, (static_cast<T>(2) * zn) / (right - left));
        m.Set(0, 2, (right + left) / (right - left));
        m.Set(1, 1, (static_cast<T>(2) * zn) / (top - bottom));
        m.Set(2, 1, (top + bottom) / (top - bottom));
        m.Set(2, 2, -((zf + zn) / (zf - zn)));
        m.Set(2, 3, -((static_cast<T>(2) * zf * zn) / (zf - zn)));
        m.Set(3, 2, static_cast<T>(-1));
        return m;
    }

    static MatrixType Perspective(T fov, T aspect, T zn, T zf)
    {
        MatrixType m;
        T uh = (fov / static_cast<T>(2)).Cos();
        T uw = uh / aspect;
        m.Set(0, 0, uw);
        m.Set(1, 1, uh);
        m.Set(2, 2, ((zf + zn) / (zf - zn)));
        m.Set(2, 3, -((2 * zf * zn) / (zf - zn)));
        m.Set(3, 2, static_cast<T>(1));
        return m;
    }

    inline T Get(size_t row, size_t col)
    {
        return m_mat[col][row];
    }

    inline void Set(size_t row, size_t col, const T value)
    {
        m_mat[col][row] = value;
    }

private:
    union
    {
        T m_mat[Cols][Rows];
        T m_data[Cols * Rows];
    };
};

template<typename T>
using Mat4x4 = Matrix<T, 4, 4>;
