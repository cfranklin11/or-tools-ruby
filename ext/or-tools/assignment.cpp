#include <ortools/graph/assignment.h>
#include <ortools/graph/max_flow.h>
#include <ortools/graph/min_cost_flow.h>

#include <rice/Array.hpp>
#include <rice/Constructor.hpp>
#include <rice/Module.hpp>

using operations_research::NodeIndex;
using operations_research::SimpleLinearSumAssignment;
using operations_research::SimpleMaxFlow;
using operations_research::SimpleMinCostFlow;

using Rice::Array;
using Rice::Symbol;

void init_assignment(Rice::Module& m) {
  Rice::define_class_under<SimpleMaxFlow>(m, "SimpleMaxFlow")
    .define_constructor(Rice::Constructor<SimpleMaxFlow>())
    .define_method("add_arc_with_capacity", &SimpleMaxFlow::AddArcWithCapacity)
    .define_method("num_nodes", &SimpleMaxFlow::NumNodes)
    .define_method("num_arcs", &SimpleMaxFlow::NumArcs)
    .define_method("tail", &SimpleMaxFlow::Tail)
    .define_method("head", &SimpleMaxFlow::Head)
    .define_method("capacity", &SimpleMaxFlow::Capacity)
    .define_method("optimal_flow", &SimpleMaxFlow::OptimalFlow)
    .define_method("flow", &SimpleMaxFlow::Flow)
    .define_method(
      "solve",
      *[](SimpleMaxFlow& self, NodeIndex source, NodeIndex sink) {
        auto status = self.Solve(source, sink);

        if (status == SimpleMaxFlow::Status::OPTIMAL) {
          return Symbol("optimal");
        } else if (status == SimpleMaxFlow::Status::POSSIBLE_OVERFLOW) {
          return Symbol("possible_overflow");
        } else if (status == SimpleMaxFlow::Status::BAD_INPUT) {
          return Symbol("bad_input");
        } else if (status == SimpleMaxFlow::Status::BAD_RESULT) {
          return Symbol("bad_result");
        } else {
          throw std::runtime_error("Unknown status");
        }
      })
    .define_method(
      "source_side_min_cut",
      *[](SimpleMaxFlow& self) {
        std::vector<NodeIndex> result;
        self.GetSourceSideMinCut(&result);

        Array ret;
        for(auto const& it: result) {
          ret.push(it);
        }
        return ret;
      })
    .define_method(
      "sink_side_min_cut",
      *[](SimpleMaxFlow& self) {
        std::vector<NodeIndex> result;
        self.GetSinkSideMinCut(&result);

        Array ret;
        for(auto const& it: result) {
          ret.push(it);
        }
        return ret;
      });

  Rice::define_class_under<SimpleMinCostFlow>(m, "SimpleMinCostFlow")
    .define_constructor(Rice::Constructor<SimpleMinCostFlow>())
    .define_method("add_arc_with_capacity_and_unit_cost", &SimpleMinCostFlow::AddArcWithCapacityAndUnitCost)
    .define_method("set_node_supply", &SimpleMinCostFlow::SetNodeSupply)
    .define_method("optimal_cost", &SimpleMinCostFlow::OptimalCost)
    .define_method("maximum_flow", &SimpleMinCostFlow::MaximumFlow)
    .define_method("flow", &SimpleMinCostFlow::Flow)
    .define_method("num_nodes", &SimpleMinCostFlow::NumNodes)
    .define_method("num_arcs", &SimpleMinCostFlow::NumArcs)
    .define_method("tail", &SimpleMinCostFlow::Tail)
    .define_method("head", &SimpleMinCostFlow::Head)
    .define_method("capacity", &SimpleMinCostFlow::Capacity)
    .define_method("supply", &SimpleMinCostFlow::Supply)
    .define_method("unit_cost", &SimpleMinCostFlow::UnitCost)
    .define_method(
      "solve",
      *[](SimpleMinCostFlow& self) {
        auto status = self.Solve();

        if (status == SimpleMinCostFlow::Status::NOT_SOLVED) {
          return Symbol("not_solved");
        } else if (status == SimpleMinCostFlow::Status::OPTIMAL) {
          return Symbol("optimal");
        } else if (status == SimpleMinCostFlow::Status::FEASIBLE) {
          return Symbol("feasible");
        } else if (status == SimpleMinCostFlow::Status::INFEASIBLE) {
          return Symbol("infeasible");
        } else if (status == SimpleMinCostFlow::Status::UNBALANCED) {
          return Symbol("unbalanced");
        } else if (status == SimpleMinCostFlow::Status::BAD_RESULT) {
          return Symbol("bad_result");
        } else if (status == SimpleMinCostFlow::Status::BAD_COST_RANGE) {
          return Symbol("bad_cost_range");
        } else {
          throw std::runtime_error("Unknown status");
        }
      });

  Rice::define_class_under<SimpleLinearSumAssignment>(m, "LinearSumAssignment")
    .define_constructor(Rice::Constructor<SimpleLinearSumAssignment>())
    .define_method("add_arc_with_cost", &SimpleLinearSumAssignment::AddArcWithCost)
    .define_method("num_nodes", &SimpleLinearSumAssignment::NumNodes)
    .define_method("num_arcs", &SimpleLinearSumAssignment::NumArcs)
    .define_method("left_node", &SimpleLinearSumAssignment::LeftNode)
    .define_method("right_node", &SimpleLinearSumAssignment::RightNode)
    .define_method("cost", &SimpleLinearSumAssignment::Cost)
    .define_method("optimal_cost", &SimpleLinearSumAssignment::OptimalCost)
    .define_method("right_mate", &SimpleLinearSumAssignment::RightMate)
    .define_method("assignment_cost", &SimpleLinearSumAssignment::AssignmentCost)
    .define_method(
      "solve",
      *[](SimpleLinearSumAssignment& self) {
        auto status = self.Solve();

        if (status == SimpleLinearSumAssignment::Status::OPTIMAL) {
          return Symbol("optimal");
        } else if (status == SimpleLinearSumAssignment::Status::INFEASIBLE) {
          return Symbol("infeasible");
        } else if (status == SimpleLinearSumAssignment::Status::POSSIBLE_OVERFLOW) {
          return Symbol("possible_overflow");
        } else {
          throw std::runtime_error("Unknown status");
        }
      });
}