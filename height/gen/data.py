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


fullMaxN = 100000
fullMaxQ = 100000
fullMaxH = 10**9

quadraticN = 2000
quadraticQ = 2000

smallH = 20


def base_gen(gen_func):
  @indexify_testcases
  def _gen_func(minN, maxN, minQ, maxQ, maxH, *args, testcase_index):
    gen_name = gen_func(*args)
    params = [gen_name, minN, maxN, minQ, maxQ, maxH] + list(args) + [testcase_index]
    print(*params)
  return _gen_func


def base_gen_no_q(gen_func):
  @indexify_testcases
  def _gen_func(minN, maxN, maxH, *args, testcase_index):
    gen_name = gen_func(*args)
    params = [gen_name, minN, maxN, maxH] + list(args) + [testcase_index]
    print(*params)
  return _gen_func


@base_gen
def gen_random():
  return "gen random"


@base_gen
def gen_random_consistent():
  return "gen random_consistent"


@base_gen
def gen_random_almost_consistent():
  return "gen random_almost_consistent"


@base_gen_no_q
def gen_query_all_then_each():
  return "gen query_all_then_each"


@base_gen_no_q
def gen_shringking_queries():
  return "gen shrinking_queries"


@base_gen_no_q
def gen_doubly_shrinking_queries():
  return "gen doubly_shrinking_queries"


@base_gen_no_q
def gen_quick_sort_queries():
  return "gen quick_sort_queries"


@base_gen
def gen_random_point_queries():
  return "gen random_point_queries"


@base_gen
def gen_random_consistent_point_queries_except_last():
  return "gen random_consistent_point_queries_except_last"


@base_gen
def gen_random_constant_difference(difference):
  return "gen random_constant_difference"


@base_gen
def gen_random_almost_consistent_constant_difference(difference):
  return "gen random_almost_consistent_constant_difference"


@base_gen_no_q
def gen_ordered_constant_difference(difference):
  return "gen ordered_constant_difference"


@base_gen
def gen_random_l_zero():
  return "gen random_l_zero"


@base_gen_no_q
def gen_random_consistent_l_zero_except_last():
  return "gen random_consistent_l_zero_except_last"


@base_gen_no_q
def gen_ordered_l_zero():
  return "gen ordered_l_zero"


@base_gen_no_q
def gen_points_then_shrinking_queries():
  return "gen points_then_shrinking_queries"


@base_gen_no_q
def gen_counter_wrong_sampling():
  return "gen counter_wrong_sampling"


def gen_common_point_queries(maxN, maxQ, maxH):
  gen_random_point_queries(maxN, maxN, maxQ, maxQ, maxH)
  gen_random_consistent_point_queries_except_last(maxN, maxN, maxQ, maxQ, maxH)


def gen_common_l_zero(maxN, maxQ, maxH):
  gen_random_l_zero(maxN, maxN, maxQ, maxQ, maxH)
  gen_random_consistent_l_zero_except_last(maxQ - 10, maxQ - 1, maxH)
  gen_ordered_l_zero(maxQ - 10, maxQ - 1, maxH)


def gen_common_constant_difference(maxN, maxQ, maxH):
  gen_random_constant_difference(maxN // 2, maxN, maxQ // 2, maxQ, maxH, maxN // 4)
  gen_random_almost_consistent_constant_difference(maxN, maxN, maxQ, maxQ, maxH, 2)
  gen_random_almost_consistent_constant_difference(maxN, maxN, maxQ, maxQ, maxH, maxN // 2)
  gen_random_almost_consistent_constant_difference(maxN, maxN, maxQ, maxQ, maxH, 10)
  gen_ordered_constant_difference(maxN, maxN, maxH, maxN // 2)


def gen_common(maxN, maxQ, maxH):
  gen_random(maxN // 2, maxN, maxQ // 2, maxQ, maxH)
  gen_random(maxN, maxN, maxQ, maxQ, maxH)
  gen_random_consistent(maxN, maxN, maxQ, maxQ, maxH)
  gen_random_almost_consistent(maxN, maxN, maxQ, maxQ, maxH)
  gen_query_all_then_each(maxQ - 10, maxQ - 2, maxH)
  gen_shringking_queries(maxQ - 10, maxQ - 1, maxH)
  gen_doubly_shrinking_queries(maxQ - 10, maxQ - 1, maxH)
  gen_quick_sort_queries(maxQ - 10, maxQ - 1, maxH)
  gen_points_then_shrinking_queries(maxN - 10, maxN - 1, maxH)


class Testset():
  name = None
  manuals = []

  def __init__(self):
    assert self.__class__.__name__.startswith(TESTSET_PREFIX)
    print("")
    print(f"@testset {self.__class__.__name__[len(TESTSET_PREFIX):]}")
    for test in self.manuals:
        manual(test)
    self.gen()

  def gen(self):
    pass


class Subtask():
  name = None

  def __init__(self):
    print("")
    print(f"@subtask {self.name}")


def generate_common_testsets(name, maxN, maxQ):
  def gen_class(name, maxH, gens):
    def gen_funcs(self):
      for gen in gens:
        gen(maxN, maxQ, maxH)

    globals()[name] = type(name, (Testset,), {'gen': gen_funcs})

  gen_class(f"Testset{name}Point", fullMaxH, [gen_common_point_queries])
  gen_class(f"Testset{name}LZero", fullMaxH, [gen_common_l_zero])
  gen_class(f"Testset{name}ConstantDifference", fullMaxH, [gen_common_constant_difference])
  gen_class(f"Testset{name}SmallH", smallH, [gen_common_point_queries, gen_common_l_zero, gen_common_constant_difference, gen_common])


generate_common_testsets('Quadratic', quadraticN, quadraticQ)
generate_common_testsets('Full', fullMaxN, fullMaxQ)

TestsetQuadraticSmallH.manuals = [
    "constant-difference-N", "constant-difference-N-2", "constant-difference-N-minus-one",
    "counter-wrong-sampling", "point-all-query",
]

class TestsetNOne(Testset):
  manuals = ["n-one-inc", "n-one-dec"]


class SubtaskSamples(Subtask):
  name = "samples"

  def __init__(self):
    super().__init__()
    manual("sample-1")


class SubtaskPoint(Subtask):
  name = "L-equals-R"

  def __init__(self):
    super().__init__()
    include(TestsetQuadraticPoint)
    include(TestsetFullPoint)
    include(TestsetNOne)


class SubtaskLZero(Subtask):
  name = "L-equals-zero"

  def __init__(self):
    super().__init__()
    include(TestsetQuadraticLZero)
    include(TestsetFullLZero)
    include(TestsetNOne)
    manual("non-increasing-L-zero")


class SubtaskQuadratic(Subtask):
  name = "quadratic"

  def __init__(self):
    super().__init__()
    include(SubtaskSamples)
    include(TestsetQuadraticSmallH)
    include(TestsetQuadraticPoint)
    include(TestsetQuadraticLZero)
    include(TestsetQuadraticConstantDifference)
    include(TestsetNOne)
    gen_common(quadraticN, quadraticQ, fullMaxH)
    gen_counter_wrong_sampling(quadraticQ // 3, quadraticQ // 3 * 2, None)


class SubtaskConstantDifference(Subtask):
  name = "constant-difference"

  def __init__(self):
    super().__init__()
    include(TestsetQuadraticConstantDifference)
    include(TestsetFullConstantDifference)
    include(SubtaskPoint)


class SubtaskSmallH(Subtask):
  name = "small-H"

  def __init__(self):
    super().__init__()
    include(SubtaskSamples)
    include(TestsetQuadraticSmallH)
    include(TestsetFullSmallH)
    gen_counter_wrong_sampling(fullMaxQ // 3, fullMaxQ // 3 * 2, None)


class SubtaskFull(Subtask):
  name = "full"

  def __init__(self):
    super().__init__()
    include(SubtaskLZero)
    include(SubtaskConstantDifference)
    include(SubtaskQuadratic)
    include(SubtaskSmallH)
    gen_common(fullMaxN, fullMaxQ, fullMaxH)


def main():
  for testset in Testset.__subclasses__():
    testset()
  for subtask in Subtask.__subclasses__():
    subtask()


if __name__ == '__main__':
  main()
