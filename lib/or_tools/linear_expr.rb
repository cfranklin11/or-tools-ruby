module ORTools
  class LinearExpr
    def coeffs
      coeffs = Hash.new(0.0)
      stack = [[1.0, self]]
      while stack.any?
        current_multiplier, current_expression = stack.pop

        # skip empty LinearExpr for backwards compatibility
        next if current_expression.instance_of?(LinearExpr)

        current_expression.add_self_to_coeff_map_or_stack(coeffs, current_multiplier, stack)
      end
      coeffs
    end

    def +(expr)
      SumArray.new([self, expr])
    end

    def -(expr)
      SumArray.new([self, -expr])
    end

    def *(other)
      ProductCst.new(self, other)
    end

    def /(cst)
      ProductCst.new(self, 1.0 / other)
    end

    def -@
      ProductCst.new(self, -1)
    end

    def ==(arg)
      if arg.is_a?(Numeric)
        LinearConstraint.new(self, arg, arg)
      else
        LinearConstraint.new(self - arg, 0.0, 0.0)
      end
    end

    def >=(arg)
      if arg.is_a?(Numeric)
        LinearConstraint.new(self, arg, Float::INFINITY)
      else
        LinearConstraint.new(self - arg, 0.0, Float::INFINITY)
      end
    end

    def <=(arg)
      if arg.is_a?(Numeric)
        LinearConstraint.new(self, -Float::INFINITY, arg)
      else
        LinearConstraint.new(self - arg, -Float::INFINITY, 0.0)
      end
    end
  end
end
