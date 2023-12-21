#line 1 "c:\\Users\\79052\\Desktop\\arduino\\smart-mixer-v4\\src\\classes\\faucet.h"
#include <SoftServo.h>

class FaucetServo: public SoftServo {
	public:
		FaucetServo(): SoftServo() {};
		void init(int pin) {

			this->attach(pin, 500, 2500);
		}

		/**
		 * увеличивает открытие крана на переданный угол
		 * 
		 * не уйдет выше максимального угла
		*/
		void increaceTarget(int angle = 0) {
			if (!angle) {
				return;
			}

			if (this->targetAngle + angle < this->endAngle) {
				this->targetAngle += angle;
			} else {
				this->targetAngle = this->endAngle;
			}
		}

		/**
		 * уменьшает открытие крана на переданный угол
		 *
		 * не уйдет ниже минимального угла
		*/
		void decreaseTarget(int angle = 0) {
			if (!angle) {
				return;
			}

			if (this->targetAngle - angle > this->startAngle) {
				this->targetAngle -= angle;
			} else {
				this->targetAngle = this->startAngle;
			}
		}

		void setTargetAngle(int angle) {
			if (data.isManual) {
				this->targetAngle = angle;
			}
		}

		bool myTick() {
			this->write(this->targetAngle);

			return this->tick();
		}

		// void close() {
		// 	this->targetAngle = this->startAngle;
		// }

		// void start() {
		// 	// не уверен что оно работает, смысл в том чтобы сначала полностью закрыть кран, а уже потом стартовать его в какую-то внятную позицию
		// 	if (!isClosed()) {
		// 		this->close();

		// 		this->myTick();
		// 	}

		// 	this->increaceTarget(60);
		// }

		// int getCurrentAngle() {
		// 	return map(this->read(), this->startAngle, this->endAngle, 0, 100);
		// }

		// bool isFullyOpen() {
		// 	return this->targetAngle == this->endAngle;
		// }

		// bool isFullyClose() {
		// 	return this->targetAngle == this->startAngle;
		// }

	private:
		int startAngle = 0;
		int endAngle = 180;
		int targetAngle = 0;
};