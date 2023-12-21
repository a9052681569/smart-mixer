#include <Arduino.h>

class Mixer {
	public:
		/**
		 * целевая температура, к ней мы всегда стремимся и стараемся удержать
		*/
		int targetTemp = 38;

		int currentTemp = 0;

		void init(void (*warmer)(int percent), void (*colder)(int percent), int targetTemp) {
			this->makeWarmer = *warmer;
			this->makeColder = *colder;
			this->targetTemp = targetTemp;
		}

		void tick(int temp, float tempChangeSpeed, int targetTemp) {
			this->currentTemp = temp;

			this->tempChangeSpeed = tempChangeSpeed;

			this->targetTemp = targetTemp;
		}

		void turnTick() {
			int optimalTurn = this->getOptimalTurn();
			int turnDirection = this->getTurnDirection();

			// в этом условии пытаемся сделать похолоднее
			if (turnDirection < 0) {
				this->makeColder(optimalTurn);
			}

			// в этом условии пытаемся сделать погорячее
			if (turnDirection > 0) {
				this->makeWarmer(optimalTurn);
			}
		}

		int getOptimalTurn() {
			int tempDifAbs = abs(this->targetTemp - this->currentTemp);

			/**
			 * чем меньше разница между текущей и целевой температурой тем точнее мы хотим регулировать краны
			 *
			 * чем медленнее поворачиваем кран тем точнее регулировка
			 * 
			 * при этом при большем проценте поворота регулировка будет проходить быстрее
			*/
			if (tempDifAbs <= 1) {
				return 1;
			} else if (tempDifAbs <= 5) {
				return tempDifAbs * 2;
			} else {
				return 10;
			}
		}

		/**
		 * возвращает направление поворота
		 * 
		 * >0 - попытаться сделать горячее
		 * <0 - попытаться сделать холоднее
		 * 0 - не делать ничего
		*/
		int getTurnDirection() {
			// желаемое направление
			int wishDirection = this->targetTemp - this->currentTemp;

			if (wishDirection == 0) {
				return 0;
			}

			// притормаживаем если летим в нужном направлении, но с высокой скоростью
			// чтобы притормозить крутим кран в обратном направлении от желаемого
			if (abs(this->tempChangeSpeed) > 2.5 && this->isPositive(wishDirection) == this->isPositive(this->tempChangeSpeed)) {
				return 0 - wishDirection;
			}

			// ждем если летим в нужном направлении не супер быстро, но и не медленно
			// так мы дождемся стабилизации температуры
			if (abs(this->tempChangeSpeed) > 0.3 && this->isPositive(wishDirection) == this->isPositive(this->tempChangeSpeed)) {
				return 0;
			}

			return wishDirection;
		}

	private:
		float tempChangeSpeed = 0;

		bool isPositive(int num) {
			return num > 0;
		}

		void (*makeWarmer)(int percent);
		void (*makeColder)(int percent);
};
