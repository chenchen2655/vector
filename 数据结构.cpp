
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <complex>
#include <random>

using namespace std;

bool cmp(const complex<double>& a, const complex<double>& b) {
    if (abs(a) == abs(b)) {
        return real(a) < real(b);
    }
    return abs(a) < abs(b);
}

void bubble_sort(vector<complex<double>>& v) {
    int n = v.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (cmp(v[j + 1], v[j])) {
                swap(v[j], v[j + 1]);
            }
        }
    }
}

void merge(vector<complex<double>>& v, int l, int m, int r) {
    vector<complex<double>> tmp(r - l + 1);
    int i = l, j = m + 1, k = 0;
    while (i <= m && j <= r) {
        if (abs(v[i]) <= abs(v[j])) {
            tmp[k++] = v[i++];
        }
        else {
            tmp[k++] = v[j++];
        }
    }
    while (i <= m) {
        tmp[k++] = v[i++];
    }
    while (j <= r) {
        tmp[k++] = v[j++];
    }
    for (int i = l; i <= r; i++) {
        v[i] = tmp[i - l];
    }
}

void merge_sort(vector<complex<double>>& v, int l, int r) {
    if (l >= r) {
        return;
    }
    int m = l + (r - l) / 2;
    merge_sort(v, l, m);
    merge_sort(v, m + 1, r);
    merge(v, l, m, r);
}




class Complex {
public:
    Complex(double realpart, double imagpart) : r(realpart), i(imagpart) {}
    double r;
    double i;
};

void shuffle_complex_vector(vector<Complex>& complex_vector) {
    random_shuffle(complex_vector.begin(), complex_vector.end());
}

int find_complex_number(vector<Complex>& complex_vector, Complex& complex_number) {
    for (int i = 0; i < complex_vector.size(); i++) {
        if (complex_vector[i].r == complex_number.r && complex_vector[i].i == complex_number.i) {
            return i;
        }
    }
    return -1;
}

void insert_complex_number(vector<Complex>& complex_vector, Complex& complex_number) {
    complex_vector.push_back(complex_number);
}

void delete_complex_number(vector<Complex>& complex_vector, Complex& complex_number) {
    int index = find_complex_number(complex_vector, complex_number);
    if (index != -1) {
        complex_vector.erase(complex_vector.begin() + index);
    }
}

vector<Complex> unique_complex_numbers(vector<Complex>& complex_vector) {
    vector<Complex> unique_complex_numbers;
    for (int i = 0; i < complex_vector.size(); i++) {
        if (find_complex_number(unique_complex_numbers, complex_vector[i]) == -1) {
            unique_complex_numbers.push_back(complex_vector[i]);
        }
    }
    return unique_complex_numbers;
}
vector<complex<double>> find_complex(const vector<complex<double>>& v, double m1, double m2) {
    vector<complex<double>> result;
    for (auto it = v.begin(); it != v.end(); ++it) {
        if (it->real() * it->real() + it->imag() * it->imag() >= m1 * m1 && it->real() * it->real() + it->imag() * it->imag() < m2 * m2) {
            result.push_back(*it);
        }
    }
    return result;
}

int main() {
    
 // 区间查找算法
    
    random_device rd; // 随机数生成器
    mt19937 gen(rd()); 
    uniform_real_distribution<> dis(-10, 10); 
    vector<complex<double>> v(10); // 长度为10的复数向量

    bool found = false;
    for (auto& i : v) {
        i.real(dis(gen)); // 生成随机实数作为实部
        i.imag(dis(gen));
        cout << i << " ";
    }
    cout << " " << endl;
    double m1 = dis(gen), m2 = dis(gen);
    if (m1 > m2) swap(m1, m2);
    cout << "m1: " << m1 << ", m2: " << m2 << endl;
    auto result = find_complex(v, m1, m2);

    for (auto& i : result) {
        cout << "找到介于m1，m2之间的复数向量：result=  " << i << endl;
        found = true;
    }
    if (!found) {
        cout << "未找到介于m1，m2之间的复数向量" << endl;
    }
    
        


    shuffle(v.begin(), v.end(), gen); // 向量置乱
    for (auto& i : v) { 
        cout << i << " ";  
    }
    cout << "置乱"<<endl;

    auto it = find(v.begin(), v.end(), complex<double>(1.0, 2.0)); // 查找元素1+2i是否在向量中出现过
    if (it != v.end()) { 
        cout << "找到: " << *it << endl;
    }
    else { 
        cout << "未找到." << endl; 
    }

    v.insert(v.begin() + 3, complex<double>(1.0, 2.0)); // 在第4个位置插入元素1+2i
    for (auto& i : v) { // 对于每个元素
        cout << i << " "; // 输出该元素
    }
    cout <<"插入"<< endl;

    v.erase(v.begin() + 5); // 删除第6个位置的元素
    for (auto& i : v) { 
        cout << i << " "; 
    }
    cout << "删除" << endl;

    auto last = unique(v.begin(), v.end()); // 唯一
    for (auto it = v.begin(); it != last; ++it) { 
        cout << *it << " ";
    }
    cout << "唯一化" << endl;

    sort(v.begin(), v.end(), cmp); // 排序
    for (auto& i : v) { // 
        cout << i << " ";
    }
    cout << endl;

    vector<complex<double>> w(1000000); // 长度为1000000的复数向量

    for (auto& i : w) { // 生成随机实数作为实部和虚部
        i.real(dis(gen));
        i.imag(dis(gen));
    }

    clock_t start = clock(); // 记录起始时间

    sort(w.begin(), w.end(), cmp); // 排序，使用自定义比较函数cmp作为排序规则

    clock_t end = clock(); // 记
    cout << "  时间： Time used by bubble sort: " << end - start << "ms" << endl; // 输出冒泡排序所用的时间

    start = clock(); // 记录起始时间

    sort(w.begin(), w.end(), cmp); // 

    end = clock(); // 记录结束时间

    cout << " 时间： Time used by merge sort: " << end - start << "ms" << endl; // 输出归并排序所用的时间
}