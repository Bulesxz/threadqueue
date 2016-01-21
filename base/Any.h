#ifndef ANY_H
#define ANY_H
#define NULL 0
namespace daocode{

class PlaceHolder
{
	public:
		virtual ~PlaceHolder(){}
		virtual PlaceHolder* clone() const{};
};



template<typename ValueType>
class Holder : public PlaceHolder {
	public:
		Holder(const ValueType& value):held_(value) {;}
		virtual ~Holder(){}
		virtual PlaceHolder* clone() const
		{
			  return new Holder(held_);
		}
	public:
		ValueType held_;
};


class Any {
	public:
		Any() : content_(NULL) {}
		template<typename ValueType>
		Any(const ValueType& value) : content_(new Holder<ValueType>(value)) {
		}

		Any(const Any& other) : content_(other.content_ ? other.content_->clone() : NULL) {}

		~Any() {
			if (content_ != NULL)
			{
				delete content_;
				content_ = NULL;
			}
		}

		template<typename ValueType>
		ValueType * any_cast() {
			if (content_ == NULL)
				return NULL;
			else
				return &(static_cast<Holder<ValueType> *>(content_)->held_);
		}



	private:
		PlaceHolder* content_;
};

}
/*
template<typename ValueType>
ValueType* any_cast() {
		if (content == NULL)
			return NULL;
		else
			return static_cast<holder<ValueType> *>(content_)->held_;
}

*/



#endif
