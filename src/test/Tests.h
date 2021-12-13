//
// Created by tobias on 21.11.16.
//

#ifndef VDSPROJECT_TESTS_H
#define VDSPROJECT_TESTS_H

#include "gtest/gtest.h"
#include "../Manager.h"

#define SAMPLE_TABLE \
{   \
{"False", 0, 0, 0, 0}, \
{ "True", 1, 1, 1, 1}, \
{    "a", 2, 1, 0, 2}, \
{    "b", 3, 1, 0, 3}, \
{    "c", 4, 1, 0, 4}, \
{    "d", 5, 1, 0, 5}, \
{  "a+b", 6, 1, 3, 2}, \
{  "c*d", 7, 5, 0, 4}, \
{"b*c*d", 8, 7, 0, 3}, \
{    "f", 9, 7, 8, 2}, \
} \

#endif
