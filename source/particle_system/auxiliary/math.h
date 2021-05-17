#pragma once

class float3 {
public:
    constexpr float3()
        : x(0.f), y(0.f), z(0.f)
    {
    }

    explicit constexpr float3(float all)
        : x(all), y(all), z(all)
    {
    }


    explicit constexpr float3(float x, float y, float z)
        : x(x), y(y), z(z)
    {
    }

    constexpr float* begin() {
        return data;
    }

    constexpr const float* begin() const {
        return data;
    }

    constexpr float* end() {
        return data + 3;
    }

    constexpr const float* end() const {
        return data + 3;
    }

    constexpr float3 operator+(const float3& rhs) const {
        return float3(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    constexpr float3 operator-(const float3& rhs) const {
        return float3(x - rhs.x, y - rhs.y, z - rhs.z);
    }

    constexpr float3 operator*(const float3& rhs) const {
        return float3(x * rhs.x, y * rhs.y, z * rhs.z);
    }

    constexpr float3 operator/(const float3& rhs) const {
        return float3(x / rhs.x, y / rhs.y, z / rhs.z);
    }

    constexpr float3& operator+=(const float3& value) {
        x += value.x;
        y += value.y;
        z += value.z;

        return *this;
    }

    constexpr float3& operator-=(const float3& value) {
        x -= value.x;
        y -= value.y;
        z -= value.z;

        return *this;
    }

    constexpr float3& operator*=(const float3& value) {
        x *= value.x;
        y *= value.y;
        z *= value.z;

        return *this;
    }

    constexpr float3& operator/=(const float3& value) {
        x /= value.x;
        y /= value.y;
        z /= value.z;

        return *this;
    }

    constexpr float3& operator*=(float value) {
        x *= value;
        y *= value;
        z *= value;

        return *this;
    }

    constexpr float3& operator/=(float value) {
        x /= value;
        y /= value;
        z /= value;

        return *this;
    }

    constexpr float& operator[](size_t index) {
        return data[index];
    }

    constexpr const float& operator[](size_t index) const {
        return data[index];
    }

    constexpr float3 operator-() const {
        return float3(-x, -y, -z);
    }

    constexpr float3 operator*(float rhs) const {
        return float3(x * rhs, y * rhs, z * rhs);
    }

    constexpr float3 operator/(float rhs) const {
        return float3(x / rhs, y / rhs, z / rhs);
    }

    constexpr bool operator==(const float3& value) const {
        return x == value.x && y == value.y && z == value.z;
    }

    constexpr bool operator!=(const float3& value) const {
        return x != value.x || y != value.y || z != value.z;
    }

    constexpr float* operator&() {
        return data;
    }

    constexpr const float* operator&() const {
        return data;
    }

    friend constexpr float3 operator*(float lhs, const float3& rhs) {
        return rhs * lhs;
    }

    union {
        struct {
            float x, y, z;
        };

        struct {
            float r, g, b;
        };

        float data[3];
    };
};

class float4 {
public:
    constexpr float4()
        : x(0.f), y(0.f), z(0.f), w(0.f)
    {
    }

    explicit constexpr float4(float all)
        : x(all), y(all), z(all), w(all)
    {
    }
    
    explicit constexpr float4(float x, float y, float z, float w)
        : x(x), y(y), z(z), w(w)
    {
    }

    explicit constexpr float4(const float3& value, float w)
        : x(value.x), y(value.y), z(value.z), w(w)
    {
    }

    constexpr float* begin() {
        return data;
    }

    constexpr const float* begin() const {
        return data;
    }

    constexpr float* end() {
        return data + 4;
    }

    constexpr const float* end() const {
        return data + 4;
    }

    constexpr float4 operator+(const float4& rhs) const {
        return float4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
    }

    constexpr float4 operator-(const float4& rhs) const {
        return float4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
    }

    constexpr float4 operator*(const float4& rhs) const {
        return float4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
    }

    constexpr float4 operator/(const float4& rhs) const {
        return float4(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
    }

    constexpr float4& operator+=(const float4& value) {
        x += value.x;
        y += value.y;
        z += value.z;
        w += value.w;

        return *this;
    }

    constexpr float4& operator-=(const float4& value) {
        x -= value.x;
        y -= value.y;
        z -= value.z;
        w -= value.w;

        return *this;
    }

    constexpr float4& operator*=(const float4& value) {
        x *= value.x;
        y *= value.y;
        z *= value.z;
        w *= value.w;

        return *this;
    }

    constexpr float4& operator/=(const float4& value) {
        x /= value.x;
        y /= value.y;
        z /= value.z;
        w /= value.w;

        return *this;
    }

    constexpr float4& operator*=(float value) {
        x *= value;
        y *= value;
        z *= value;
        w *= value;

        return *this;
    }

    constexpr float4& operator/=(float value) {
        x /= value;
        y /= value;
        z /= value;
        w /= value;

        return *this;
    }

    constexpr float& operator[](size_t index) {
        return data[index];
    }

    constexpr const float& operator[](size_t index) const {
        return data[index];
    }

    constexpr float4 operator-() const {
        return float4(-x, -y, -z, -w);
    }

    constexpr float4 operator*(float rhs) const {
        return float4(x * rhs, y * rhs, z * rhs, w * rhs);
    }

    constexpr float4 operator/(float rhs) const {
        return float4(x / rhs, y / rhs, z / rhs, w / rhs);
    }

    constexpr bool operator==(const float4& value) const {
        return x == value.x && y == value.y && z == value.z && w == value.w;
    }

    constexpr bool operator!=(const float4& value) const {
        return x != value.x || y != value.y || z != value.z || w != value.w;
    }

    constexpr float* operator&() {
        return data;
    }

    constexpr const float* operator&() const {
        return data;
    }

    friend constexpr float4 operator*(float lhs, const float4& rhs) {
        return rhs * lhs;
    }

    union {
        float3 xyz;

        struct {
            float x, y, z, w;
        };

        struct {
            float r, g, b, a;
        };

        float data[4];
    };
};

class float4x4 {
public:
    constexpr float4x4()
        : _11(1.f), _12(0.f), _13(0.f), _14(0.f)
        , _21(0.f), _22(1.f), _23(0.f), _24(0.f)
        , _31(0.f), _32(0.f), _33(1.f), _34(0.f)
        , _41(0.f), _42(0.f), _43(0.f), _44(1.f)
    {
    }

    explicit constexpr float4x4(float _11, float _12, float _13, float _14,
                                float _21, float _22, float _23, float _24,
                                float _31, float _32, float _33, float _34,
                                float _41, float _42, float _43, float _44)
        : _11(_11), _12(_12), _13(_13), _14(_14)
        , _21(_21), _22(_22), _23(_23), _24(_24)
        , _31(_31), _32(_32), _33(_33), _34(_34)
        , _41(_41), _42(_42), _43(_43), _44(_44)
    {
    }

    constexpr float4x4(const float4& _r0, const float4& _r1, const float4& _r2, const float4& _r3)
        : _r0(_r0), _r1(_r1), _r2(_r2), _r3(_r3) {
    }

    constexpr float* begin() {
        return cells;
    }

    constexpr const float* begin() const {
        return cells;
    }

    constexpr float* end() {
        return cells + 16;
    }

    constexpr const float* end() const {
        return cells + 16;
    }

    constexpr float4x4 operator+(const float4x4& rhs) const {
        return float4x4(_11 + rhs._11, _12 + rhs._12, _13 + rhs._13, _14 + rhs._14,
                        _21 + rhs._21, _22 + rhs._22, _23 + rhs._23, _24 + rhs._24,
                        _31 + rhs._31, _32 + rhs._32, _33 + rhs._33, _34 + rhs._34,
                        _41 + rhs._41, _42 + rhs._42, _43 + rhs._43, _44 + rhs._44);
    }

    constexpr float4x4 operator-(const float4x4& rhs) const {
        return float4x4(_11 - rhs._11, _12 - rhs._12, _13 - rhs._13, _14 - rhs._14,
                        _21 - rhs._21, _22 - rhs._22, _23 - rhs._23, _24 - rhs._24,
                        _31 - rhs._31, _32 - rhs._32, _33 - rhs._33, _34 - rhs._34,
                        _41 - rhs._41, _42 - rhs._42, _43 - rhs._43, _44 - rhs._44);
    }

    constexpr float4x4 operator*(const float4x4& rhs) const {
        return float4x4(_11 * rhs._11 + _12 * rhs._21 + _13 * rhs._31 + _14 * rhs._41,
                        _11 * rhs._12 + _12 * rhs._22 + _13 * rhs._32 + _14 * rhs._42,
                        _11 * rhs._13 + _12 * rhs._23 + _13 * rhs._33 + _14 * rhs._43,
                        _11 * rhs._14 + _12 * rhs._24 + _13 * rhs._34 + _14 * rhs._44,
                        _21 * rhs._11 + _22 * rhs._21 + _23 * rhs._31 + _24 * rhs._41,
                        _21 * rhs._12 + _22 * rhs._22 + _23 * rhs._32 + _24 * rhs._42,
                        _21 * rhs._13 + _22 * rhs._23 + _23 * rhs._33 + _24 * rhs._43,
                        _21 * rhs._14 + _22 * rhs._24 + _23 * rhs._34 + _24 * rhs._44,
                        _31 * rhs._11 + _32 * rhs._21 + _33 * rhs._31 + _34 * rhs._41,
                        _31 * rhs._12 + _32 * rhs._22 + _33 * rhs._32 + _34 * rhs._42,
                        _31 * rhs._13 + _32 * rhs._23 + _33 * rhs._33 + _34 * rhs._43,
                        _31 * rhs._14 + _32 * rhs._24 + _33 * rhs._34 + _34 * rhs._44,
                        _41 * rhs._11 + _42 * rhs._21 + _43 * rhs._31 + _44 * rhs._41,
                        _41 * rhs._12 + _42 * rhs._22 + _43 * rhs._32 + _44 * rhs._42,
                        _41 * rhs._13 + _42 * rhs._23 + _43 * rhs._33 + _44 * rhs._43,
                        _41 * rhs._14 + _42 * rhs._24 + _43 * rhs._34 + _44 * rhs._44);
    }

    constexpr float4x4& operator+=(const float4x4& value) {
        _11 += value._11;
        _12 += value._12;
        _13 += value._13;
        _14 += value._14;
        _21 += value._21;
        _22 += value._22;
        _23 += value._23;
        _24 += value._24;
        _31 += value._31;
        _32 += value._32;
        _33 += value._33;
        _34 += value._34;
        _41 += value._41;
        _42 += value._42;
        _43 += value._43;
        _44 += value._44;

        return *this;
    }

    constexpr float4x4& operator-=(const float4x4& value) {
        _11 -= value._11;
        _12 -= value._12;
        _13 -= value._13;
        _14 -= value._14;
        _21 -= value._21;
        _22 -= value._22;
        _23 -= value._23;
        _24 -= value._24;
        _31 -= value._31;
        _32 -= value._32;
        _33 -= value._33;
        _34 -= value._34;
        _41 -= value._41;
        _42 -= value._42;
        _43 -= value._43;
        _44 -= value._44;

        return *this;
    }

    constexpr float4x4& operator*=(const float4x4& value) {
        float4x4 temp(
            _11 * value._11 + _12 * value._21 + _13 * value._31 + _14 * value._41,
            _11 * value._12 + _12 * value._22 + _13 * value._32 + _14 * value._42,
            _11 * value._13 + _12 * value._23 + _13 * value._33 + _14 * value._43,
            _11 * value._14 + _12 * value._24 + _13 * value._34 + _14 * value._44,
            _21 * value._11 + _22 * value._21 + _23 * value._31 + _24 * value._41,
            _21 * value._12 + _22 * value._22 + _23 * value._32 + _24 * value._42,
            _21 * value._13 + _22 * value._23 + _23 * value._33 + _24 * value._43,
            _21 * value._14 + _22 * value._24 + _23 * value._34 + _24 * value._44,
            _31 * value._11 + _32 * value._21 + _33 * value._31 + _34 * value._41,
            _31 * value._12 + _32 * value._22 + _33 * value._32 + _34 * value._42,
            _31 * value._13 + _32 * value._23 + _33 * value._33 + _34 * value._43,
            _31 * value._14 + _32 * value._24 + _33 * value._34 + _34 * value._44,
            _41 * value._11 + _42 * value._21 + _43 * value._31 + _44 * value._41,
            _41 * value._12 + _42 * value._22 + _43 * value._32 + _44 * value._42,
            _41 * value._13 + _42 * value._23 + _43 * value._33 + _44 * value._43,
            _41 * value._14 + _42 * value._24 + _43 * value._34 + _44 * value._44
        );

        return *this = temp;
    }

    constexpr float4x4& operator*=(float value) {
        _11 *= value;
        _12 *= value;
        _13 *= value;
        _14 *= value;
        _21 *= value;
        _22 *= value;
        _23 *= value;
        _24 *= value;
        _31 *= value;
        _32 *= value;
        _33 *= value;
        _34 *= value;
        _41 *= value;
        _42 *= value;
        _43 *= value;
        _44 *= value;

        return *this;
    }

    constexpr float4x4& operator/=(float value) {
        _11 /= value;
        _12 /= value;
        _13 /= value;
        _14 /= value;
        _21 /= value;
        _22 /= value;
        _23 /= value;
        _24 /= value;
        _31 /= value;
        _32 /= value;
        _33 /= value;
        _34 /= value;
        _41 /= value;
        _42 /= value;
        _43 /= value;
        _44 /= value;

        return *this;
    }

    constexpr float4& operator[](size_t index) {
        return rows[index];
    }

    constexpr const float4& operator[](size_t index) const {
        return rows[index];
    }

    constexpr float4x4 operator-() const {
        return float4x4(-_11, -_12, -_13, -_14,
                        -_21, -_22, -_23, -_24,
                        -_31, -_32, -_33, -_34,
                        -_41, -_42, -_43, -_44);
    }

    constexpr float4x4 operator*(float rhs) const {
        return float4x4(_11 * rhs, _12 * rhs, _13 * rhs, _14 * rhs,
                        _21 * rhs, _22 * rhs, _23 * rhs, _24 * rhs,
                        _31 * rhs, _32 * rhs, _33 * rhs, _34 * rhs,
                        _41 * rhs, _42 * rhs, _43 * rhs, _44 * rhs);
    }

    constexpr float4 operator*(const float4& rhs) const {
        return float4(_11 * rhs.x + _12 * rhs.y + _13 * rhs.z + _14 * rhs.w,
                      _21 * rhs.x + _22 * rhs.y + _23 * rhs.z + _24 * rhs.w,
                      _31 * rhs.x + _32 * rhs.y + _33 * rhs.z + _34 * rhs.w,
                      _41 * rhs.x + _42 * rhs.y + _43 * rhs.z + _44 * rhs.w);
    }

    constexpr float3 operator*(const float3& rhs)  const{
        return float3(_11 * rhs.x + _12 * rhs.y + _13 * rhs.z,
                      _21 * rhs.x + _22 * rhs.y + _23 * rhs.z,
                      _31 * rhs.x + _32 * rhs.y + _33 * rhs.z);
    }

    constexpr bool operator==(const float4x4& value) const {
        return _11 == value._11 && _12 == value._12 && _13 == value._13 && _14 == value._14 &&
               _21 == value._21 && _22 == value._22 && _23 == value._23 && _24 == value._24 &&
               _31 == value._31 && _32 == value._32 && _33 == value._33 && _34 == value._34 &&
               _41 == value._41 && _42 == value._42 && _43 == value._43 && _44 == value._44;
    }

    constexpr bool operator!=(const float4x4& value) const {
        return _11 != value._11 || _12 != value._12 || _13 != value._13 || _14 != value._14 ||
               _21 != value._21 || _22 != value._22 || _23 != value._23 || _24 != value._24 ||
               _31 != value._31 || _32 != value._32 || _33 != value._33 || _34 != value._34 ||
               _41 != value._41 || _42 != value._42 || _43 != value._43 || _44 != value._44;
    }

    constexpr float* operator&() {
        return cells;
    }

    constexpr const float* operator&() const {
        return cells;
    }

    friend constexpr float4x4 operator*(float lhs, const float4x4& rhs) {
        return rhs * lhs;
    }

    friend constexpr float4 operator*(const float4& lhs, const float4x4& rhs) {
        return float4(lhs.x * rhs._11 + lhs.y * rhs._21 + lhs.z * rhs._31 + lhs.w * rhs._41,
                      lhs.x * rhs._12 + lhs.y * rhs._22 + lhs.z * rhs._32 + lhs.w * rhs._42,
                      lhs.x * rhs._13 + lhs.y * rhs._23 + lhs.z * rhs._33 + lhs.w * rhs._43,
                      lhs.x * rhs._14 + lhs.y * rhs._24 + lhs.z * rhs._34 + lhs.w * rhs._44);
    }

    friend constexpr float3 operator*(const float3& lhs, const float4x4& rhs) {
        return float3(lhs.x * rhs._11 + lhs.y * rhs._21 + lhs.z * rhs._31,
                      lhs.x * rhs._12 + lhs.y * rhs._22 + lhs.z * rhs._32,
                      lhs.x * rhs._13 + lhs.y * rhs._23 + lhs.z * rhs._33);
    }

    union {
        struct {
            float _m00, _m01, _m02, _m03;
            float _m10, _m11, _m12, _m13;
            float _m20, _m21, _m22, _m23;
            float _m30, _m31, _m32, _m33;
        };

        struct {
            float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;
            float _41, _42, _43, _44;
        };

        struct {
            float4 _r0;
            float4 _r1;
            float4 _r2;
            float4 _r3;
        };

        float4 rows[4];
        float cells[16];
    };
};
