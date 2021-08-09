# KNN Classifier

## Implementation
To keep the code generic, we created an interface called `Classifiable`:
```c++
template<class T>
class Classifiable {
    virtual double distance(const T &other) const = 0;
    virtual std::string getType() const = 0;
};
```
In our case the only class implementing `Classifiable` is `Iris`:
```c++
class Iris : public Classifiable<Iris> {...};
```
The `KNNClassifier` is also a template, it gets a `Classifiable` as a generic type:
```c++
template<class T>
class KnnClassifier {
    static_assert(std::is_base_of<Classifiable<T>, T>::value, "T must be subclass of Classifiable!");
    ...
}
```
We are using `static_assert` to make sure the generic type indeed implements the `Classifiable` interface.

`KNNClassifier` holds a vector of the classified objects, which it gets via the constructor.
It also has a `classify` method:
```c++
std::string classify(T &unclassified) {...}
```
who's job is to predict the type of the unclassified object based on our data.
`classify` sorts the data vector based on the distances between any `T` in the date and `unclassified`.
The comparison is done by a functor called `Comparator`.

Then we copy the first `k` elements of the sorted vector into another vector.
The next step is to find the type that appears the most among the elements in the vector.

We are using a `map` called `predictions` to store the number of occurrences per type:
```c++
std::map<std::string, int> predictions;
```
`classify` will return the key which value is the highest.
## Running
You can run the project using our provided `CMakeLists.txt` file:
```
mkdir build
cd build
cmake ..
make
./AP1 <path-to-classified.csv> <path-to-unclassified.csv> <path-to-output.csv>
```