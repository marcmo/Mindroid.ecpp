/*
 * Copyright (C) 2011 Daniel Himmelein
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MINDROID_LOOPER_H_
#define MINDROID_LOOPER_H_

#include <pthread.h>
#include "mindroid/os/Message.h"
#include "mindroid/os/MessageQueue.h"
#include "mindroid/os/RunnableQueue.h"
#include "mindroid/util/Utils.h"
#include "mindroid/Mindroid.h"

namespace mindroid {

class Runnable;

class Looper
{
public:
	virtual ~Looper() {}
	static bool prepare();
	static Looper* myLooper();
	static void loop();
	void quit();

	MessageQueue& myMessageQueue() {
		return mMessageQueue;
	}

private:
	Looper();
	static void init();
	static void finalize(void* looper);

	RunnableQueue& myRunnableQueue() {
		return mRunnableQueue;
	}

	static pthread_once_t sTlsOneTimeInitializer;
	static pthread_key_t sTlsKey;
	static uint8_t sLooperHeapMemory[];
	static Looper* sLoopers[MAX_NUM_LOOPERS];
	static Lock sLock;
	static int sNumLoopers;

	MessageQueue mMessageQueue;
	RunnableQueue mRunnableQueue;
	Message mMessage;

	friend class Handler;

	NO_COPY_CTOR_AND_ASSIGNMENT_OPERATOR(Looper)
};

} /* namespace mindroid */

#endif /* MINDROID_LOOPER_H_ */
