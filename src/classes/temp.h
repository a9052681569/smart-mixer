#include <GyverNTC.h>

class TempController: public GyverNTC {
	public:
	 	TempController(int pin, int resistance, int base, uint32_t Rt = 10000): GyverNTC(pin, resistance, base, 25, Rt) {}
		/**
		 * текущая целая температура, подходит для большей части вычислений, сравнений и т.д
		*/
		int currentIntTemp = 0;

		/**
		 * скорость изменения температуры
		 * 
		 * Положительное значение значит что температура растет
		 * 
		 * Отрицательное значит что температура падает
		*/
		float tempChangeSpeed = 0;

		void tick() {
			this->calcTemp();
			this->calcSpeed();
		}

	private:
		/**
		 * точная температура при последнем опросе
		*/
		float lastTemp = 0;
		/**
		 * точная текущая температура
		*/
		float currentFloatTemp = 0;

		void calcTemp() {
			// читаем и сохраняем текущую температуру
			this->currentFloatTemp = getTempAverage();
			
			bool isBigAbsDifference = abs(this->currentFloatTemp - this->lastTemp) > 0.5;
			bool isIntDifference = int(this->currentFloatTemp) != int(this->lastTemp);

			if (isBigAbsDifference && isIntDifference) {
				// присваиваем новую температуру
				this->currentIntTemp = this->currentFloatTemp;
				this->lastTemp = this->currentFloatTemp;
			}
		};

		long tempChangeSpeedTimestamp = 0;

		int unsigned tempChangeSpeedDelay = 1000;

		float tempChangeSpeedLastTemp = 0;

		void calcSpeed() {
			// если прошло больше времени чем мы заложили в tempChangeSpeedDelay
			if (millis() - this->tempChangeSpeedTimestamp > this->tempChangeSpeedDelay) {
				this->tempChangeSpeed = (this->currentFloatTemp - this->tempChangeSpeedLastTemp);

				this->tempChangeSpeedLastTemp = this->currentFloatTemp;

				this->tempChangeSpeedTimestamp = millis();
			}
		}
};
