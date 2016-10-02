/*
 * qrs_detection_task.h
 *
 *  Created on: Sep 8, 2016
 *      Author: root
 */

#ifndef INC_QRS_DETECTION_TASK_H_
#define INC_QRS_DETECTION_TASK_H_

static int test_flag = 0;

int qrs_detection_task_get_test_flag();
void qrs_detection_task_set_test_flag();
void qrs_detection_task_drop_test_flag();

void qrs_detection_task();

#endif /* INC_QRS_DETECTION_TASK_H_ */
