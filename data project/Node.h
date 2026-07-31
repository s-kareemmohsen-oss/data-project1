template<typename T>
class Node {
private:
	T data;
	Node<T>* next;
public:
	Node() {
		next = nullptr;
	}
	Node(const T& value, Node<T>* nextPtr = nullptr)
		: data(value), next(nextPtr) {
	}
	const T& getData() const {
		return data;
	}
	Node<T>* getNext() const {
		return next;
	}
	void setNext(Node<T>* other) {
		next = other;
	}
	void setData(const T& other) {
		data = other;
	}
};