#include "Vector.h"

Vector::Vector() {
    initialize(2);
}

Vector::Vector(int dimension) {
    initialize(dimension);
}

Vector::Vector(int size, const double elements[]) {
    initialize(size);
    for(int i = 0; i < size; i++) {
        fElements[i] = elements[i];
    }
}

Vector::Vector(const Vector &source) {
    initialize(source.getDimension());
    for(int i = 0; i < fDimension; i++) {
        fElements[i] = source[i];
    }
}

Vector::~Vector() {
    delete fElements;
}

int Vector::getDimension() const {
    return fDimension;
}

void Vector::setDimension(int dimension) {
    //extend memory allocate
    if(dimension > allocSize) {
        allocSize = dimension;
        fElements = (double*)realloc(fElements, allocSize * sizeof(double));
    }

    //extend dimension(fDimension < dimension)
    while(fDimension < dimension) {
        fElements[fDimension] = 0;
        fDimension++;
    }

    //reduce dimension(fDimension > dimension)
    fDimension = dimension;
}

void Vector::initialize(int size) {
    fElements = (double*)malloc(size * sizeof(double));
    allocSize = fDimension = size;
}

Vector& Vector::operator=(const Vector source) {
    setDimension(source.getDimension());
    for(int i = 0; i < fDimension; i++) {
        fElements[i] = source[i];
    }

    return *this;
}

double& Vector::operator[](int index) {
    if(index >= fDimension) {
        cout << "Index out of range.\n";
        static double zerod = 0;
        return zerod;
    }
    return fElements[index];
}

double Vector::operator[](int index) const {
    if(index >= fDimension) {
        cout << "Index out of range.\n";
        return 0;
    }
    return fElements[index];
}

Vector Vector::operator+(const Vector &v2) const {
    if(v2.getDimension() != fDimension) {
        cout << "Dimensions are not equality";
        return *this;
    }

    Vector output(*this);
    for(int i = 0; i < fDimension; i++) {
        output[i] += v2[i];
    }

    return output;
}

Vector Vector::operator-(const Vector &v2) const {
    if(v2.getDimension() != fDimension) {
        cout << "Dimensions are not equality";
        return *this;
    }
    
    Vector output(*this);
    for(int i = 0; i < fDimension; i++) {
        output[i] -= v2[i];
    }

    return output;
}

Vector& Vector::operator+=(const Vector &v2) {
    if(v2.getDimension() != fDimension) {
        cout << "Dimensions are not equality";
        return *this;
    }
    
    for(int i = 0; i < fDimension; i++) {
        fElements[i] += v2[i];
    }

    return *this;
}

Vector& Vector::operator-=(const Vector &v2) {
    if(v2.getDimension() != fDimension) {
        cout << "Dimensions are not equality";
        return *this;
    }

    for(int i = 0; i < fDimension; i++) {
        fElements[i] -= v2[i];
    }

    return *this;
}

Vector Vector::operator-() const {
    Vector output(*this);

    for(int i = 0; i < fDimension; i++) {
        output[i] *= -1;
    }

    return output;
}

Vector operator*(double scale, Vector v) {
    Vector output(v);

    for(int i = 0; i < output.getDimension(); i++) {
        output[i] *= scale;
    }

    return output;
}

Vector Vector::operator*(double scale) const {
    Vector output(*this);

    for(int i = 0; i < fDimension; i++) {
        output[i] *= scale;
    }

    return output;
}

Vector& Vector::operator*=(double scale) {
    for(int i = 0; i < fDimension; i++) {
        fElements[i] *= scale;
    }

    return *this;
}

bool Vector::operator==(const Vector &v2) const {
    if(fDimension != v2.getDimension()) return false;
    
    for(int i = 0; i < fDimension; i++) {
        if(fElements[i] != v2[i]) return false;
    }

    return true;
}

bool Vector::operator!=(const Vector &v2) const {
    if(fDimension != v2.getDimension()) return true;
    
    for(int i = 0; i < fDimension; i++) {
        if(fElements[i] != v2[i]) return true;
    }

    return false;
}

double Vector::length() const {
    double sum = 0;
    for(int i = 0; i < fDimension; i++) {
        sum += pow(fElements[i], 2);
    }

    return sqrt(sum);
}

ostream& operator<<(ostream &os, const Vector &v) {
    bool printed = false;
    os << '(';
    for(int i = 0; i < v.getDimension(); i++) {
        if(printed) os << ", ";
        else printed = true;
        os << v[i];
    }
    os << ')';
    return os;
}
