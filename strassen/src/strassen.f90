module strassen 
contains 
recursive subroutine strassen_mul(a, b, c, n, strass)
    integer, intent(in) :: n, strass
    real(8), intent(in) :: a(n,n), b(n,n)
    real(8), intent(out) :: c(n,n)

    real(8), dimension(N/2,N/2) :: sub1, sub2, arg1, arg2, res

    if (N == strass) then
        c = matmul(a,b)
    else
        arg1 = a(:N/2, :N/2) + a(N/2+1:, N/2+1:)    !a11 + a22
        arg2 = b(:N/2, :N/2) + b(N/2+1:, N/2+1:)    !b11 + b22
        call strassen_mul(arg1, arg2, res, N/2, strass) !d
        c(:N/2, :N/2) = res                         !c11 = d
        c(N/2+1:, N/2+1:) = res                     !c22 = d
        
        arg1 = a(:N/2, N/2+1:) - a(N/2+1:, N/2+1:)  !a12 - a22
        arg2 = b(N/2+1:, :N/2) + b(N/2+1:, N/2+1:)  !b21 + b22
        call strassen_mul(arg1, arg2, res, N/2, strass) !d1
        c(:N/2, :N/2) = c(:N/2, :N/2) + res         !c11 += d1
        
        arg1 = a(N/2+1:, :N/2) - a(:N/2, :N/2)      !a21 - a11
        arg2 = b(:N/2, :N/2) + b(:N/2, N/2+1:)      !b11 + b12
        call strassen_mul(arg1, arg2, res, N/2, strass) !d2
        c(N/2+1:, N/2+1:) = c(N/2+1:, N/2+1:) + res !c22 += d2
        
        arg1 = a(:N/2, :N/2) + a(:N/2, N/2+1:)      !a11 + a12
        arg2 = b(N/2+1:, N/2+1:)                    !b22
        call strassen_mul(arg1, arg2, res, N/2, strass) !h1
        c(:N/2, :N/2) = c(:N/2, :N/2) - res         !c11 -= h1
        c(:N/2, N/2+1:) = res                       !c12 = h1
        
        arg1 = a(N/2+1:, :N/2) + a(N/2+1:, N/2+1:)  !a12 + a22
        arg2 = b(:N/2, :N/2)                        !b11
        call strassen_mul(arg1, arg2, res, N/2, strass) !h2
        c(N/2+1:, :N/2) = res                       !c21 = h2
        c(N/2+1:, N/2+1:) = c(N/2+1:, N/2+1:) - res !c22 -= h2
        
        arg1 = a(N/2+1:, N/2+1:)                    !a22
        arg2 = b(N/2+1:, :N/2) - b(:N/2, :N/2)      !b21 - b11
        call strassen_mul(arg1, arg2, res, N/2, strass) !v1
        c(:N/2, :N/2) = c(:N/2, :N/2) + res         !c11 += v1
        c(N/2+1:, :N/2) = c(N/2+1:, :N/2) + res     !c21 += v1
        
        arg1 = a(:N/2, :N/2)                        !a11
        arg2 = b(:N/2, N/2+1:) - b(N/2+1:, N/2+1:)  !b12 - b22
        call strassen_mul(arg1, arg2, res, N/2, strass) !v2
        c(:N/2, N/2+1:) = c(:N/2, N/2+1:) + res     !c12 += v2
        c(N/2+1:, N/2+1:) = c(N/2+1:, N/2+1:) + res !c22 += v2
    end if

    return
end subroutine strassen_mul

end module strassen
