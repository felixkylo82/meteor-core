/*
 * OmdCircularBuffer.hpp
 *
 *  Created on: Jul 25, 2015
 *      Author: felix
 */

#ifndef CIRCULARBUFFER_HPP_
#define CIRCULARBUFFER_HPP_

namespace meteor {
	namespace core {
		template<typename T, int CAPACITY, int N = CAPACITY + 1>
		class CircularBuffer {
		private:
			int start;
			int end;
			T items[N];

		public:
			CircularBuffer() :
					start(0), end(0) {
			}

			inline bool isEmpty() const {
				return start == end;
			}

			inline int length() const {
				return (end - start + N) % N;
			}

			inline bool isFull() const {
				return length() >= CAPACITY;
			}

			inline void push_front(const T& item) {
				start = (start + N - 1) % N;
				items[start] = item;
			}

			inline void push_back(const T& item) {
				items[end] = item;
				end = (end + 1) % N;
			}

			inline bool pop_front(T& item) {
				if (isEmpty())
					return false;
				item = items[start];
				start = (start + 1) % N;
				return true;
			}

			inline bool pop_back(T& item) {
				if (isEmpty())
					return false;
				end = (end + N - 1) % N;
				item = items[end];
				return true;
			}

			inline bool insert(int pos, const T& item) {
				if (pos < 0 || pos >= length())
					return false;
				pos = (start + pos + 1) % N;

				if (isFull()) {
					end = (end + N - 1) % N;
				}

				int i = end;
				int j;
				while (i != pos) {
					j = (i + N - 1) % N;
					items[i] = items[j];
					i = j;
				}
				items[pos] = item;

				end = (end + 1) % N;

				return true;
			}

			inline bool update(int pos, const T& item) {
				if (pos < 0 || pos >= length())
					return false;
				pos = (start + pos) % N;

				items[pos] = item;

			}
		};
	}
}

#endif /* CIRCULARBUFFER_HPP_ */
