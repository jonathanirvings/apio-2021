TESTSET_PREFIX = "Testset"


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


@indexify_testcases
def constant_array(N, M, X, testcase_index):
  print(f"gen constant-array {N} {M} {X} {testcase_index}")

@indexify_testcases
def identity_array(N, testcase_index):
  print(f"gen identity-array {N} {testcase_index}")

@indexify_testcases
def divided_by_M(N, M, testcase_index):
  print(f"gen divided-by-M {N} {M} {testcase_index}")

@indexify_testcases
def alternating_corner(N, M, testcase_index):
  print(f"gen alternating-corner {N} {M} {testcase_index}")

@indexify_testcases
def two_blocks(N, M, X, L, R, testcase_index):
  print(f"gen two-blocks {N} {M} {X} {L} {R} {testcase_index}")

@indexify_testcases
def zig_zag(N, M, testcase_index):
  print(f"gen zig-zag {N} {M} {testcase_index}")

@indexify_testcases
def sorted_non_descending(N, M, testcase_index):
  print(f"gen sorted-non-descending {N} {M} {testcase_index}")

@indexify_testcases
def sorted_non_ascending(N, M, testcase_index):
  print(f"gen sorted-non-ascending {N} {M} {testcase_index}")

@indexify_testcases
def half_array(N, M, testcase_index):
  print(f"gen half-array {N} {M} {testcase_index}")

@indexify_testcases
def full_array(N, M, testcase_index):
  print(f"gen full-array {N} {M} {testcase_index}")

def common_testcases(maxN, maxM):
  constant_array(maxN, maxM, maxM)
  constant_array(maxN, maxM, maxM//2)
  zig_zag(maxN, maxM)
  zig_zag(maxN-1, maxM)
  sorted_non_descending(maxN, maxM)
  sorted_non_ascending(maxN, maxM)
  half_array(maxN, maxM)
  full_array(maxN, maxM)
  half_array(maxN-1, maxM-1)
  full_array(maxN-5, maxM//2)

def special_testcases(maxN, maxM, types):
  L, R = maxM//4, 3*maxM//4
  if types == 1:
    L, R = 0, maxM
  two_blocks(maxN, maxM, maxN//2, L, R)
  two_blocks(maxN, maxM, 2*maxN//3, L, R)
  two_blocks(maxN, maxM, maxN//4, L, R)
  two_blocks(maxN, maxM, 5*maxN//8, L, R)


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


class TestsetNano(Testset):
  def __init__(self):
    super().__init__()
    common_testcases(10, 10)

class TestsetMicro(Testset):
  def __init__(self):
    super().__init__()
    common_testcases(20, 20)

class TestsetSmall(Testset):
  def __init__(self):
    super().__init__()
    common_testcases(30, 30)

class TestsetMedium(Testset):
  def __init__(self):
    super().__init__()
    common_testcases(200, 200)
    common_testcases(200, 100000)
    special_testcases(200, 100000, 0)

class TestsetLarge(Testset):
  def __init__(self):
    super().__init__()
    common_testcases(2000, 2000)
    common_testcases(2000, 100000)
    special_testcases(2000, 100000, 0)

class TestsetCorner(Testset):
  def __init__(self):
    super().__init__()
    constant_array(2000, 100000, 0)
    constant_array(2000, 100000, 100000)
    divided_by_M(2000, 1)
    divided_by_M(2000, 100000)
    alternating_corner(2000, 1)
    alternating_corner(2000, 100000)
    special_testcases(2000, 100000, 1)

class TestsetLine(Testset):
  def __init__(self):
    super().__init__()
    identity_array(1023)
    identity_array(1024)
    identity_array(1025)
    identity_array(1999)
    identity_array(2000)


class SubtaskSamples(Subtask):
  name = "samples"

  def __init__(self):
    super().__init__()
    manual("sample-1")


class SubtaskNano(Subtask):
  name = "bruteforce"

  def __init__(self):
    super().__init__()
    include(SubtaskSamples)
    include(TestsetNano)
    
    manual("small-1")
    manual("small-2")


class SubtaskMicro(Subtask):
  name = "exponential"

  def __init__(self):
    super().__init__()
    include(SubtaskNano)
    include(TestsetMicro)


class SubtaskSmall(Subtask):
  name = "fifth"

  def __init__(self):
    super().__init__()
    include(SubtaskMicro)
    include(TestsetSmall)


class SubtaskCorner(Subtask):
  name = "M-divides-A_i"

  def __init__(self):
    super().__init__()
    include(TestsetCorner)
    
    manual("small-1")
    manual("small-2")


class SubtaskLine(Subtask):
  name = "A_i-equals-i"

  def __init__(self):
    super().__init__()
    include(TestsetLine)
    
    manual("small-2")


class SubtaskMedium(Subtask):
  name = "cubic"

  def __init__(self):
    super().__init__()
    include(SubtaskSmall)
    include(TestsetMedium)


class SubtaskLarge(Subtask):
  name = "full"

  def __init__(self):
    super().__init__()
    include(SubtaskMedium)
    include(TestsetLarge)


def main():
  for testset in Testset.__subclasses__():
    testset()
  for subtask in Subtask.__subclasses__():
    subtask()

main()
