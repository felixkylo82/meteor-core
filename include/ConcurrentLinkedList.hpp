/*
 * ConcurrentLinkedList.hpp
 *
 *  Created on: Jul 27, 2015
 *      Author: felix
 */

#ifndef CONCURRENTLINKEDLIST_HPP_
#define CONCURRENTLINKEDLIST_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/atomic.hpp>
#include <boost/pool/object_pool.hpp>

namespace meteor {
	namespace core {
		// A lock-free linked list that supports only push_back and traversal
		template<typename T>
		class ConcurrentLinkedList {
		public:
			template<typename S>
			struct Node {
				boost::shared_ptr<S> item;
				boost::atomic<Node<S>*> next;

				Node(const boost::shared_ptr<S>& item) :
						item(item) {
					next.store(0, boost::memory_order_release);
				}

				virtual ~Node() {
				}

				inline Node<S>* getNext() const {
					return next.load(boost::memory_order_consume);
				}
			};

		private:
			static boost::object_pool<Node<T>> pool;

		private:
			boost::atomic<Node<T>*> head;
			boost::atomic<Node<T>*> tail;

		public:
			ConcurrentLinkedList(Node<T>* _head = pool.construct()) {
				head.store(_head, boost::memory_order_release);
			}

			virtual ~ConcurrentLinkedList() {
				while (popFront()) {
				}
				pool.destroy(head.exchange(0));
			}

			inline ConcurrentLinkedList clear() {
				return ConcurrentLinkedList(head.exchange(pool.construct()));
			}

			inline Node<T>* getFrontNode() const {
				return head.load(boost::memory_order_acquire)->getNext();
			}

			inline void pushBack(const boost::shared_ptr<T>& item) {
				Node<T>* newTail = pool.construct(item);

				Node<T>* _tail;
				Node<T>* _next;
				do {
					_tail = tail.load(boost::memory_order_acquire);
					_next = _tail->next.load(boost::memory_order_acquire);
					while (_next) {
						_tail = _next;
						_next = _tail->next.load(boost::memory_order_acquire);
					}
				} while (_tail->next.compare_exchange_weak(0, newTail));

				tail.store(newTail, boost::memory_order_relaxed);
			}

		private:
			inline boost::shared_ptr<T> popFront() {
				Node<T>* _head;
				Node<T>* newHead;
				do {
					_head = head.load(boost::memory_order_acquire);
					newHead = _head->next.load(boost::memory_order_acquire);
				} while (head.compare_exchange_weak(_head, newHead));
				pool.destroy(_head);

				boost::shared_ptr<T> item = newHead->item;
				newHead->item.reset((T*) 0);
				return item;
			}
		};
	} /* namespace core */
} /* namespace meteor */

#endif /* CONCURRENTLINKEDLIST_HPP_ */
