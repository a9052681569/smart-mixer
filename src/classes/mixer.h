#include <Arduino.h>

class Mixer {
	public:
		/**
		 * целевая температура, к ней мы всегда стремимся и стараемся удержать
		*/
		int targetTemp = 38;

		int currentFloatTemp = 0;

		void init(void (*warmer)(int percent), void (*colder)(int percent), int targetTemp) {
			this->makeWarmer = *warmer;
			this->makeColder = *colder;
			this->targetTemp = targetTemp;
		}

		void tick(int currentFloatTemp, float tempChangeSpeed, int targetTemp) {
			this->currentFloatTemp = currentFloatTemp;

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
			float tempDifAbs = abs(this->targetTemp - this->currentFloatTemp);

			/**
			 * чем меньше разница между текущей и целевой температурой тем точнее мы хотим регулировать краны
			 *
			 * чем медленнее поворачиваем кран тем точнее регулировка
			 * 
			 * при этом при большем проценте поворота регулировка будет проходить быстрее
			*/
			if (tempDifAbs <= 1.5) {
				return 1;
			} else if (tempDifAbs <= 3) {
				return tempDifAbs * 2;
			} else {
				return 20;
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
			int tempDif = this->targetTemp - this->currentFloatTemp;

			// ждем если гуляем около целевой температуры
			if (abs(tempDif) <= 0.5) {
				return 0;
			}

			// притормаживаем если летим с высокой скоростью
			// чтобы притормозить крутим кран в обратном направлении от желаемого
			if (abs(this->tempChangeSpeed) > 2.5) {
				return 0 - tempDif;
			}

			// ждем если летим не супер быстро, но и не медленно
			// так мы дождемся стабилизации температуры
			if (abs(this->tempChangeSpeed) > 0.1) {
				return 0;
			}

			return tempDif;
		}

	private:
		float tempChangeSpeed = 0;

		// bool isPositive(int num) {
		// 	return num > 0;
		// }

		void (*makeWarmer)(int percent);
		void (*makeColder)(int percent);
};
