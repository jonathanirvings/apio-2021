TESTSET_PREFIX = 'Testset'


def manual(testcase):
  print(f"manual {testcase}.in")

def include(include):
  print(f"@include {include.name or include.__name__[len(TESTSET_PREFIX):]}")

def indexify_testcases(gen_func):
  testcase_index = 0
  def _gen_func(*args):
    nonlocal testcase_index
    gen_func(*args, testcase_index=testcase_index)
    testcase_index += 1
  return _gen_func


maxN = 100000
maxQ = 100000
maxElem = 1000000000


@indexify_testcases
def gen_random(minN, maxN, minQ, maxQ, minElem, maxElem,
               xEqualsOne, yEqualsOne, testcase_index):
  print(f"gen random {minN} {maxN} {minQ} {maxQ} {minElem} {maxElem} "
        f"{xEqualsOne} {yEqualsOne} {testcase_index}")

@indexify_testcases
def gen_sqrt(minN, maxN, minQ, maxQ, testcase_index):
  print(f"gen sqrt {minN} {maxN} {minQ} {maxQ} {testcase_index}")

@indexify_testcases
def gen_must_jump(minN, maxN, minQ, maxQ, minElem, maxElem, testcase_index):
  print(f"gen must-jump {minN} {maxN} {minQ} {maxQ} {minElem} {maxElem} "
        f"{testcase_index}")

@indexify_testcases
def gen_must_use_binary_search(minN, maxN, minQ, maxQ, minElem, maxElem,
                               testcase_index):
  print(f"gen must-use-binary-search {minN} {maxN} {minQ} {maxQ} "
        f"{minElem} {maxElem} {testcase_index}")

@indexify_testcases
def gen_must_memoize_answer(minN, maxN, minQ, maxQ, minElem, maxElem,
                            testcase_index):
  print(f"gen must-memoize-answer {minN} {maxN} {minQ} {maxQ} "
        f"{minElem} {maxElem} {testcase_index}")


class Testset():
  name = None

  def __init__(self):
    assert self.__class__.__name__.startswith(TESTSET_PREFIX)
    print("")
    print(f"@testset {self.__class__.__name__[len(TESTSET_PREFIX):]}")


class Subtask():
  name = None

  def __init__(self):
    print("")
    print(f"@subtask {self.name}")


class TestsetSmallestCase(Testset):
  def __init__(self):
    super().__init__()
    manual("smallest-case")


class TestsetMustJumpXEqualsOne(Testset):
  def __init__(self):
    super().__init__()
    gen_must_jump(maxN, maxN, maxQ, maxQ, 1, 1)


class TestsetMustUseBinarySearchXEqualsOne(Testset):
  def __init__(self):
    super().__init__()
    gen_must_use_binary_search(maxN, maxN, maxQ, maxQ, 1, 1)


class TestsetMustMemoizeAnswerXEqualsOne(Testset):
  def __init__(self):
    super().__init__()
    gen_must_memoize_answer(maxN, maxN, maxQ, maxQ, 1, 1)


class TestsetXYEqualsOne(Testset):
  def __init__(self):
    super().__init__()
    gen_random(maxN, maxN, maxQ, maxQ, 1, 100, 1, 1)
    gen_random(maxN, maxN, maxQ, maxQ, maxElem - 100, maxElem, 1, 1)


class SubtaskSamples(Subtask):
  name = "samples"

  def __init__(self):
    super().__init__()
    manual("sample-1")
    manual("sample-2")


class SubtaskB_iEqualsI(Subtask):
  name = "B_i-equals-i"

  def __init__(self):
    super().__init__()
    include(TestsetSmallestCase)
    include(TestsetMustJumpXEqualsOne)
    gen_sqrt(maxN, maxN, maxQ, maxQ)
    gen_must_jump(maxN, maxN, maxQ, maxQ, 2, maxElem)


class SubtaskQLessThanFive(Subtask):
  name = "Q-less-than-five"
  maxQ = 5

  def __init__(self):
    super().__init__()
    include(SubtaskSamples)
    include(TestsetSmallestCase)
    gen_must_use_binary_search(maxN, maxN, self.maxQ, self.maxQ, 2, maxElem)
    gen_random(maxN, maxN, self.maxQ, self.maxQ, 1, 100, 1, 1)
    gen_random(maxN // 10, maxN // 2 - 1, self.maxQ, self.maxQ, 1, 100, 0, 0)
    gen_random(maxN // 2, maxN - 1, self.maxQ, self.maxQ, 1, 100, 0, 0)
    gen_random(maxN, maxN, self.maxQ, self.maxQ, 1, 100, 0, 0)


class SubtaskYEqualsOne(Subtask):
  name = "Y-equals-one"

  def __init__(self):
    super().__init__()
    include(TestsetSmallestCase)
    include(TestsetXYEqualsOne)
    include(TestsetMustMemoizeAnswerXEqualsOne)
    gen_must_memoize_answer(maxN, maxN, maxQ, maxQ, 2, maxElem)
    gen_random(maxN, maxN, maxQ, maxQ, 1, 100, 0, 1)


class SubtaskXEqualsOne(Subtask):
  name = "X-equals-one"

  def __init__(self):
    super().__init__()
    include(TestsetSmallestCase)
    include(TestsetXYEqualsOne)
    include(TestsetMustJumpXEqualsOne)
    include(TestsetMustUseBinarySearchXEqualsOne)
    include(TestsetMustMemoizeAnswerXEqualsOne)
    gen_random(maxN, maxN, maxQ, maxQ, 1, 100, 1, 0)
    gen_random(maxN, maxN, maxQ, maxQ, maxElem - 100, maxElem, 1, 0)


class SubtaskFull(Subtask):
  name = "full"

  def __init__(self):
    super().__init__()
    include(SubtaskSamples)
    include(TestsetSmallestCase)
    include(SubtaskB_iEqualsI)
    include(SubtaskQLessThanFive)
    include(SubtaskYEqualsOne)
    include(SubtaskXEqualsOne)
    gen_must_use_binary_search(maxN, maxN, maxQ, maxQ, 2, maxElem)
    gen_random(maxN // 10, maxN // 2 - 1, maxQ // 10, maxQ // 2 - 1,
               1, 100, 0, 0)
    gen_random(maxN // 2, maxN - 1, maxQ // 2, maxQ - 1, 1, 100, 0, 0)
    gen_random(maxN, maxN, maxQ, maxQ, 1, 100, 0, 0)
    gen_random(maxN, maxN, maxQ, maxQ, maxElem - 100, maxElem, 0, 0)
    gen_random(maxN, maxN, maxQ, maxQ, 1, maxElem, 0, 0)


def main():
  for testset in Testset.__subclasses__():
    testset()
  for subtask in Subtask.__subclasses__():
    subtask()

main()
