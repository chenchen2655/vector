using Rank = unsigned int; //��
#define DEFAULT_CAPACITY  3 //Ĭ�ϵĳ�ʼ������ʵ��Ӧ���п�����Ϊ����
template <typename T> class Vector { //����ģ����
protected:
    Rank _size; Rank _capacity;  T* _elem; //��ģ��������������
    void copyFrom(T const* A, Rank lo, Rank hi); //������������A[lo, hi)
    void expand(); //�ռ䲻��ʱ����
    void shrink(); //װ�����ӹ�Сʱѹ��
    bool bubble(Rank lo, Rank hi); //ɨ�轻��
    void bubbleSort(Rank lo, Rank hi); //���������㷨
    Rank maxItem(Rank lo, Rank hi); //ѡȡ���Ԫ��
    void selectionSort(Rank lo, Rank hi); //ѡ�������㷨
    void merge(Rank lo, Rank mi, Rank hi); //�鲢�㷨
    void mergeSort(Rank lo, Rank hi); //�鲢�����㷨
    void heapSort(Rank lo, Rank hi); //�������Ժ�����ȫ�ѽ��⣩
    Rank partition(Rank lo, Rank hi); //��㹹���㷨
    void quickSort(Rank lo, Rank hi); //���������㷨
    void shellSort(Rank lo, Rank hi); //ϣ�������㷨
public:
    // ���캯��
    Vector(Rank c = DEFAULT_CAPACITY, Rank s = 0, T v = 0) //����Ϊc����ģΪs������Ԫ�س�ʼΪv
    {
        _elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);
    } //s<=c
    Vector(T const* A, Rank n) { copyFrom(A, 0, n); } //�������帴��
    Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //����
    Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); } //�������帴��
    Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //����
    // ��������
    ~Vector() { delete[] _elem; } //�ͷ��ڲ��ռ�
    // ֻ�����ʽӿ�
    Rank size() const { return _size; } //��ģ
    bool empty() const { return !_size; } //�п�
    Rank find(T const& e) const { return find(e, 0, _size); } //���������������
    Rank find(T const& e, Rank lo, Rank hi) const; //���������������
    Rank search(T const& e) const //���������������
    {
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }
    Rank search(T const& e, Rank lo, Rank hi) const; //���������������
    // ��д���ʽӿ�
    T& operator[] (Rank r); //�����±������������������������ʽ���ø�Ԫ��
    const T& operator[] (Rank r) const; //����������ֵ�����ذ汾
    Vector<T>& operator= (Vector<T> const&); //���ظ�ֵ���������Ա�ֱ�ӿ�¡����
    T remove(Rank r); //ɾ����Ϊr��Ԫ��
    Rank remove(Rank lo, Rank hi); //ɾ����������[lo, hi)֮�ڵ�
    Rank insert(Rank r, T const& e); //����Ԫ��
    Rank insert(T const& e) { return insert(_size, e); } //Ĭ����ΪĩԪ�ز���
    void sort(Rank lo, Rank hi); //��[lo, hi)����
    void sort() { sort(0, _size); } //��������
    void unsort(Rank lo, Rank hi); //��[lo, hi)����
    void unsort() { unsort(0, _size); } //��������
    Rank deduplicate(); //����ȥ��
    Rank uniquify(); //����ȥ��
    // ����
    void traverse(void (*) (T&)); //������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�
    template <typename VST> void traverse(VST&); //������ʹ�ú������󣬿�ȫ�����޸ģ�
}; //Vector
  
template <typename T>Rank Vector<T>::
find(T const& e, Rank lo, Rank hi)const {//˳�����
    while ((lo < hi--) && (e != _elem[hi]));
    return hi;
}
template <typename T>Rank Vector<T>::
insert(Rank r, T const& e) {//����
    expend();
    for (rank i = _size; i > r; i--)  _elem[i] = _elem[i - 1];
    _elem[r] = e;  _size++;
    return r;
}
template <typename T>Rank Vector<T>::
remove(Rank lo, Rank hi) {//����ɾ��
    if (lo == hi) return 0;
    while (hi < _size)  _elem[lo++] = _elem[hi++];  // [hi,_size)˳��ǰ��hi-lo����Ԫ
    _size = lo;
    shrink();  //���б�Ҫ��������
    return hi - lo;
}
template <typename T> T Vector<T>::
 remove(Rank r) {//��Ԫ��ɾ��
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}
template <typename T>Rank Vector<T>::
deduplicate() {//��һ��
    int oldsize = _size;
    Rank i = 1;
    while (i < _size)
        (find(_elem[i], 0, i) < 0) ? i++ : remove(i);
    return oldsize - _size;
}
template <typename T> void Vector<T>::unsort(Rank lo, Rank hi) { //�ȸ������������������[lo, hi)
    T* V = _elem + lo; //��������_elem[lo, hi)������һ����V[0, hi - lo)
    for (Rank i = hi - lo; i > 0; i--) //�Ժ���ǰ
        swap(V[i - 1], V[rand() % i]); //��V[i - 1]��V[0, i)��ĳһԪ���������
}