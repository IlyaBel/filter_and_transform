#ifndef FILTER_AND_TRANSFORM_H
#define FILTER_AND_TRANSFORM_H

#include <iterator>
#include <algorithm>
#include <vector>
#include <utility>

template <class Container, class Predicate>
class FilterView;

template <class Container, class Predicate>
class FilterIterator;

template <class Container, class Predicate>
class TransformView;

template <class Container, class Predicate>
class TransformIterator;

template <class Container, class Predicate>
class FilterIterator {
private:
    const FilterView<Container,Predicate>& view_;
    using Iterator = decltype(std::begin(std::declval<Container>()));
    Iterator value_;

public:
    FilterIterator(const FilterView<Container,Predicate>& view_0, Iterator value_0) :
        view_(view_0), value_(value_0) {}

    auto operator * () const {
        return *value_;
    }

    auto& operator ++ () {
        value_ = std::find_if(value_+1, std::end(view_.cont_), view_.pred_);
        return *this;
    }

    auto operator ++ (int) {
        auto tmp {*this};
        operator++();
        return tmp;
    }

    bool operator == (const FilterIterator& rhs) const{
        return value_ == rhs.value_;
    }

    bool operator != (const FilterIterator& rhs) const{
        return !(*this == rhs);
    }
};

template <class Container, class Predicate>
class FilterView {
private:
    const Container& cont_;
    const Predicate pred_;

public:
    FilterView(const Container& cont_0, const Predicate& pred_0) :
        cont_(cont_0), pred_(pred_0) {}

    auto begin() const{
        return FilterIterator(*this,
            std::find_if(std::begin(cont_), std::end(cont_), pred_));
    }

    auto end() const{
        return FilterIterator(*this, std::end(cont_));
    }

     friend class FilterIterator<Container, Predicate>;
};

template <class Container, class Predicate>
class TransformIterator {
private:
    const TransformView<Container,Predicate>& view_;
    using Iterator = decltype(std::begin(std::declval<Container>()));
    Iterator value_;

public:
    TransformIterator(const TransformView<Container,Predicate>& view_0, Iterator value_0) :
        view_(view_0), value_(value_0) {}

    auto operator * () const {
        return view_.pred_(*value_);
    }

    auto& operator ++ () {
        value_++;
        return *this;
    }

    auto operator ++ (int) {
        auto tmp {*this};
        operator++();
        return tmp;
    }

    bool operator == (const TransformIterator& rhs) const{
        return value_ == rhs.value_;
    }

    bool operator != (const TransformIterator& rhs) const{
        return !(*this == rhs);
    }
};

template <class Container, class Predicate>
class TransformView {
private:
    const Container& cont_;
    const Predicate pred_;

public:
    TransformView(const Container& cont_0, const Predicate& pred_0) :
        cont_(cont_0), pred_(pred_0) {}

    auto begin() const{
        return TransformIterator(*this, std::begin(cont_));
    }

    auto end() const{
        return TransformIterator(*this, std::end(cont_));
    }

    friend class TransformIterator<Container, Predicate>;
};

#endif // FILTER_AND_TRANSFORM_H
