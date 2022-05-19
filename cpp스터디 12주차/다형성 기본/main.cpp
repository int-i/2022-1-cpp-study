﻿#include <iostream>
using std::cin;
using std::cout;
using std::endl;

// 다형성(polymorphism)
// 다형성에는 여러가지가 있다. 함수 오버로딩 같은 임시 다형성이나, 형 변환 같은 강제 다형성이나,
// 템플릿 같은 매개변수 다형성 등이 있지만, 여기서 다룰 다형성은
// 하나의 객체가 여러 타입을 가질 수 있게끔 하는 서브타입 다형성을 의미한다.
// 통상적으로 객체 지향 프로그래밍에서 말하는 다형성은 이 서브타입 다형성이다.
// 
// 기초 클래스 또는 어떠한 인터페이스를 구현하는 상위 클래스를 생성하고,
// 해당 클래스를 상속받는 다수의 하위 클래스들을 만들어
// 상위 클래스의 포인터나 레퍼런스(참조 변수) 등이 하위 클래스의 객체를 참조하게 하는 것이다.
// 
// 이 때 각각의 하위 클래스는 상위 클래스의 메서드 위에 자신의 메서드를 덮어쓰는
// 메서드 오버라이딩(method overriding)을 수행하며,
// 상위 클래스의 참조 변수가 어떤 하위 클래스의 객체를 참조하느냐에 따라 호출되는 메서드가 달라진다.
// 
// 이 메서드 오버라이딩은 정적 바인딩이냐 동적 바인딩이냐에 따라 동작이 달라짐.
// 
// 바인딩: 프로그래머가 ​코딩을 해서 컴파일을 하게 되면 각각의 코드가 메모리 어딘가에 저장되고,
// 함수를 호출하는 부분에는 그 함수가 저장된 메모리의 주소값이 저장되며 프로그래머가 값을 변경할 수 없는 상태가 된다.
// 
// 여기서 함수를 호출하는 부분(호출부)을 함수가 위치한 메모리 번지(정의부)로 연결시킨 것을 바인딩이라고 한다!
// 
// 정적 바인딩: 컴파일 타임에 호출 될 함수가 확정 되는 것
// 동적 바인딩: 런타임에 호출 될 함수가 확정 되는 것
// 
// C++는 정적 바인딩을 기본으로 한다.
// 따라서 동적 바인딩을 해주기 위해서는 virtual 키워드를 통해 함수를 가상 함수로 만들어주고,
// 참조 변수를 통해, 가리킬 객체가 결정되었을 때 바인딩이 되게끔 해야 한다.
// 
// 정적 바인딩
// 장점: 컴파일 시 이미 값이 확정되어있기 때문에 실행시 효율이 높아진다. 값이 변하지 않아서 안정적
// 단점: 호출할 메서드를 실행시간에는 무슨짓을 해도 변경할 수 없기 때문에 유연성이 떨어짐.
// 
// 동적 바인딩
// 장점: 유연하고 값이 변할 수 있다.
// 단점: 어떤 값이 들어올지 몰라 메모리 공간이 낭비될 수 있고, 속도가 늦다.

class A {
public:
	A() : x{ 10 } {
		cout << "A 생성" << endl;
	}

	// virtual 키워드를 붙이지 않는다면,
	// 동적 바인딩이 성립하지 않는다.
	// 소멸자 역시 마찬가지
	virtual ~A() {
		cout << "A 소멸" << endl;
	}


	// virtual 키워드를 붙이지 않는다면,
	// 동적 바인딩이 성립하지 않는다.
	virtual void 계산() {
		x *= x;
	}


	auto getX() {
		return x;
	}

	void setX(int x) {
		this->x = x;
	}

private:
	int x;
};

class B : public A {
public:
	B()
		// 상속받은 부모 클래스의 멤버변수를 초기화 하기 위해
		// 멤버 이니셜라이저를 통해 부모 클래스의 생성자 호출
		: A{ } {
		cout << "B 생성" << endl;
	};

	virtual ~B() {
		cout << "B 소멸" << endl;
	}

	// 오버라이딩 하는 메서드는 override를 붙여줄 수 있다.
	// 다만 이건 프로그래머가 보기 좋으라고 쓰는거라 const 처럼 안붙여도 컴파일은 됨.
	// 나중에 헷갈리지 말라고 붙인다고 생각하면 좋을 듯.
	void 계산() override {
		setX(getX() + getX());
	}
};


// 이런식으로 상속을 받을 때 public을 붙여주지 않아도 상속자체는 되지만,
// 업캐스팅이 안되기 때문에 서브타입 다형성을 활용할 수 없음.
class C : A {
public:
	C() : A{ } {
		cout << "C 생성" << endl;
	};
};

int main() {
	// 포인터를 이용한 서브타입 다형성
	// new 키워드를 통해 힙 영역에 B 타입을 가지는 익명 객체를 선언하고,
	// 그 객체의 주소를 A 타입의 pa 포인터 객체가 가리킴
	A* pa{ new B{ } };

	// 레퍼런스(참조 변수)를 이용한 서브타입 다형성
	// new 키워드를 통해 힙 영역에 B 타입을 가지는 익명 객체를 선언하고,
	// 그 객체를 B 타입의 ra 레퍼런스 객체가 가리킴
	// 그래서 지금 B 익명 객체를 선언하자마자 *를 통해 디레퍼런싱을 하고 있음.
	A& ra{ *new B{ } };


	// 질문1. 여기서 pa 또는 ra의 생성자가 호출되었는가?

	pa->계산();
	cout << pa->getX() << endl;

	ra.계산();
	cout << ra.getX() << endl;

	delete pa;
	delete& ra;

	// 당연하지만 이런식으로 포인터가 해제된 이후 다시 해당 포인터의 위치에 접근하려하면 안됨!!!
	//cout << pa->getX() << endl;
	//cout << ra.getX() << endl;

	return 0;
}
